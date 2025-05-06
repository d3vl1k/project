#include <stdio.h>
#include "filesystem.h"

int main() {
    const char *filename = "test.txt";

    create_file(filename);
    write_to_file(filename, "Hello, world!\n");
    printf("File content:\n");
    read_file(filename);

    return 0;
}
