#include "../mini_lib.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        mini_printf("Usage: ", argv[0], " <file1> <file2>\n");
        return 1;
    }

    mini_quickdiff(argv[1], argv[2]);  // Call mini_quickdiff with the two files to be compared
    return 0;
}
