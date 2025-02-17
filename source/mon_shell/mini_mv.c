#include "../mini_lib.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        mini_printf("Usage: ", argv[0], " <source> <destination>\n");
        return 1;
    }

    mini_mv(argv[1], argv[2]);  // Call mini_mv with the source and destination paths
    return 0;
}
