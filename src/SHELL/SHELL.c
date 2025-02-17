#include "../mini_lib.h"
// Ajoutez ici vos déclarations de fonctions mini_lib

#define BUFFER 512
#define DEBUG 0

int read_command(char* command, char* arg[], char* fdest);
int run_command(char* command, char* arg[], char* fdest);
void load_bashrc();  // Prototypage de la fonction

#include <unistd.h>  // For getcwd()
#include <limits.h>  // For PATH_MAX

char launch_dir[PATH_MAX];  // Global variable to store the launch directory

int main() {
    char command[BUFFER];
    char fdest[BUFFER];
    char* arg[BUFFER];
    int nb_args, i;

    // Save the launch directory
    if (getcwd(launch_dir, sizeof(launch_dir)) == NULL) {
        mini_perror("getcwd");
        mini_exit(EXIT_FAILURE);
    }

    load_bashrc();  // Load ~/.mini_bashrc

    while (1) {
        // Print the prompt with the current directory
        mini_printf("\n┌──(Lambda@Xpert)'s mini_shell- [");
        mini_pwd();  // Show the current directory
        mini_printf("]\n└─λ ");
        fdest[0] = '\0'; // Initialize the destination file string

        // Read a command to execute
        nb_args = read_command(command, arg, fdest);
        arg[0] = command;  // Set the command as the first argument

        // Exit the shell if the command is 'exit'
        if (nb_args == -1) {
            mini_printf("Exit\n");
            mini_exit(EXIT_SUCCESS);
        }

        if (DEBUG) {
            mini_printf("Command to execute: ", command,", ", mini_itoa(nb_args)," arguments [");
            for (i = 0; i < nb_args; i++) {
                mini_printf("%s%s", arg[i], (i < nb_args - 1) ? ", " : "");
            }
            mini_printf("], fdest: ", fdest,"\n");
        }

        // Execute the command
        run_command(command, arg, fdest);

        // Update the prompt after executing the command
        mini_printf("\n");
    }
}

int read_command(char* command, char* arg[], char* fdest) {
    int count = 0;
    int c;

    // Read the command
    scanf("%s", command);
    if (mini_strcmp(command, "exit") == 0) {
        return -1; // Indicate exit
    }
    arg[count++] = command; // Add command to arguments

    // Read the arguments
    while (1) {
        char str[BUFFER]; // Use a local array instead of malloc
        c = getchar();
        if (c == '\n' || c == EOF) {
            break; // End of command
        }
        ungetc(c, stdin); // Put back the character read

        scanf("%s", str);
        if (mini_strcmp(str, ">") == 0) {
            // Read the output file
            scanf("%s", fdest);
            break;
        }
        arg[count++] = strdup(str); // Duplicate the string for arg
    }

    arg[count] = NULL; // Null-terminate the argument list

    // Return the number of arguments
    return count;
}

int run_command(char* command, char* arg[], char* fdest) {
    // Handle mini_cd in the parent process
    if (mini_strcmp(command, "mini_cd") == 0) {
        mini_cd(arg[1]);  // arg[1] is the directory path
        return 0;  // Return success
    }

    // Fork and execute other commands
    pid_t status;
    int fd;

    status = fork();
    switch (status) {
    case -1:
        mini_perror("Process creation failed");
        exit(EXIT_FAILURE);
    case 0:
        // Child process
        // Is there an output file?
        if (mini_strlen(fdest) > 0) {
            fd = open(fdest, O_WRONLY | O_CREAT | O_TRUNC, 0666);
            if (fd == -1) {
                mini_perror("Error opening file");
                mini_exit(EXIT_FAILURE);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd); // Close fd after duplicating
        }

        // Construct the full path to the executable
        char executable_path[PATH_MAX];
        snprintf(executable_path, sizeof(executable_path), "%s/%s", launch_dir, command);

        // Check if the executable exists in the launch directory
        if (access(executable_path, X_OK) == 0) {
            // Execute the command using the full path
            if (execv(executable_path, arg) == -1) {
                mini_perror("Error executing command");
                mini_exit(EXIT_FAILURE);
            }
        } else {
            // Use execvp to execute the command from PATH
            if (execvp(command, arg) == -1) {
                mini_perror("Error executing command");
                mini_exit(EXIT_FAILURE);
            }
        }

        exit(EXIT_SUCCESS);
    default:
        // Parent process
        // Wait for the command to finish
        wait(&status);
        if (WIFEXITED(status)) {
            mini_printf("Command executed without error\n");
        } else {
            mini_printf("Command executed with error\n");
        }
    }
}

// Fonction pour charger le fichier ~/.mini_bashrc
void load_bashrc() {
    char* home = getenv("HOME");  // Obtenir le répertoire personnel
    if (home == NULL) {
        mini_printf("Erreur: Impossible de récupérer le répertoire personnel.\n");
        return;
    }

    char bashrc_path[BUFFER];
    snprintf(bashrc_path, sizeof(bashrc_path), "%s/.mini_bashrc", home);  // Créer le chemin du fichier

    FILE* file = fopen(bashrc_path, "r");  // Ouvrir le fichier en mode lecture
    if (file == NULL) {
        if (errno != ENOENT) {  // Ne pas afficher d'erreur si le fichier n'existe pas
            mini_perror("Erreur lors de l'ouverture de ~/.mini_bashrc");
        }
        return;
    }

    char line[BUFFER];
    while (fgets(line, sizeof(line), file) != NULL) {  // Lire chaque ligne
        // Supprimer le saut de ligne à la fin
        line[strcspn(line, "\n")] = '\0';
        
        char* arg[BUFFER];  // Tableau pour les arguments
        char fdest[BUFFER] = "";  // Chaîne de destination du fichier
        int nb_args = read_command(line, arg, fdest);  // Lire la commande

        if (nb_args > 0) {
            run_command(arg[0], arg, fdest);  // Exécuter la commande
        }
    }

    fclose(file);  // Fermer le fichier
}