#include "../mini_lib.h"


int main(int argc, char *argv[]) {
    if (argc < 2) {
        mini_printf("Usage: ", argv[0], " <variable_name>\n");
        return 1;
    }

    mini_export(argv[1]);  // Call mini_getenv with the variable name
    return 0;
}
