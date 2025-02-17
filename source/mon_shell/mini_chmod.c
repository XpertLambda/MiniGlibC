#include "../mini_lib.h"
#include <stdlib.h>  // For strtol

int main(int argc, char *argv[]) {
    if (argc < 3) {
        mini_printf("Usage: ", argv[0], " <filename> <mode>\n");
        return 1;
    }

    // Convert the mode from string to an integer (octal)
    int mode = strtol(argv[2], NULL, 8);  // Assuming mode is provided as an octal string

    mini_chmod(argv[1], mode);  // Call mini_chmod with the file and mode
    return 0;
}
