#include "../mini_lib.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        mini_printf("Usage: ", argv[0], " <string>\n");
        return 1;
    }

    // Concatenate all command line arguments into a single string
    for (int i = 1; i < argc; i++) {
        mini_echo(argv[i]);
        if (i < argc - 1) {
            mini_printf(" ");  // Add space between words
        }
    }
    mini_printf("\n");  // Add newline at the end
    return 0;
}
