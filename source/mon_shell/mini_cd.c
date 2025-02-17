#include "../mini_lib.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        mini_printf("Usage: ", argv[0], " <directory>\n");
        return 1;
    }

    mini_cd(argv[1]);  // Call mini_cd with the directory path
    return 0;
}
