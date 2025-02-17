#include "../mini_lib.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        mini_printf("Usage: ", argv[0]," <filename>\n");
        return 1;
    }
    mini_cat(argv[1]);
    return 0;
}   