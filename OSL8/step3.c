#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    char buffer[atoi(argv[2])];
    FILE *fp;
    fp = fopen(argv[1], "rb");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }
    while (fread(buffer, 1, sizeof(buffer), fp)) {
    }

    fclose(fp);
    return 0;
}
