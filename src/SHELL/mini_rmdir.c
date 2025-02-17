#include "../mini_lib.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        mini_printf("Usage: ", argv[0], " <directory>\n");
        return 1;
    }

    mini_rmdir(argv[1]);  // Call mini_rmdir with the directory to be removed
    return 0;
}
