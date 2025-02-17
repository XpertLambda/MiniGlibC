#include "../mini_lib.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        mini_printf("Usage: ", argv[0], " <filename>\n");
        return 1;
    }

    mini_rm(argv[1]);  // Call mini_rm with the file to be removed
    return 0;
}
