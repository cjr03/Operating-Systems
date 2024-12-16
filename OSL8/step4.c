#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char buffer[atoi(argv[2])];
    FILE *fp, *cp;
    fp = fopen(argv[1], "rb");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }
    char filename[50];
    strcpy(filename, "copy_");
    strcat(filename, argv[1]);
    cp = fopen(filename, "wb");
    if (cp == NULL) {
        perror("Error opening file");
        return 1;
    }
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
        fwrite(buffer, 1, bytes, cp);
    }
    
    fclose(cp);
    fclose(fp);
    return 0;
}
