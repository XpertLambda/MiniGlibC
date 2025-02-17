#include "../mini_lib.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        mini_printf("Usage: ", argv[0], " <filename> <N>\n");
        return 1;
    }
    int N = atoi(argv[2]);  // Convert the string to an integer
    if (N < 1) {
        mini_printf("Error: Please provide a positive integer for the number of lines.\n");
        return 1;
    }
    mini_tail(argv[1], N);
    return 0;
}
