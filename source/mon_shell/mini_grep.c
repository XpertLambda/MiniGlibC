#include "../mini_lib.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        mini_printf("Usage: ", argv[0], " <keyword> <filename>\n");
        return 1;
    }

    mini_grep(argv[1], argv[2]);  // Call mini_grep with the keyword and filename
    return 0;
}
