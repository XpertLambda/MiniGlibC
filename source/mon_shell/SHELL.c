#include "../mini_lib.h"
// Ajoutez ici vos déclarations de fonctions mini_lib

#define BUFFER 512
#define DEBUG 0

int read_command(char* command, char* arg[], char* fdest);
int run_command(char* command, char* arg[], char* fdest);
void load_bashrc();  // Prototypage de la fonction

int main() {
    char command[BUFFER];
    char fdest[BUFFER];
    char* arg[BUFFER];
    int nb_args, i;

    load_bashrc();  // Charger le fichier ~/.mini_bashrc au démarrage

    while (1) {
        mini_printf("\n┌──(Ahmad@Saad)'s mini_shell- [");
        mini_pwd();
        mini_printf("]\n└─λ ");
        fdest[0] = '\0'; // Initialiser la chaîne de destination du fichier

        // Lire une commande à exécuter
        nb_args = read_command(command, arg, fdest);
        arg[0] = command;  // Définir la commande comme le premier argument

        // Quitter le shell si la commande est 'exit'
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

        // Exécuter la commande
        run_command(command, arg, fdest);
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
    pid_t status;
    int fd;

    status = fork();
    switch (status) {
    case -1:
        mini_perror("Process creation failed");
        exit(EXIT_FAILURE);
    case 0:
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

        // Use execv to execute the command
        if (execvp(command, arg) == -1) { // Use execvp to find the command in PATH
            mini_perror("Error executing command");
            mini_exit(EXIT_FAILURE);
        }

        exit(EXIT_SUCCESS);
    default:
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
