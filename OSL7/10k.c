#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    FILE *fp;
    char buffer[20]; // Adjust buffer size as needed
    int i;

    if (argc != 3) {
        printf("Usage: %s <someNumber> <capNumber>\n", argv[0]);
        return 1;
    }
    int someNumber = atoi(argv[1]);
    int capNumber = atoi(argv[2]);

    fp = fopen("testInput10k.txt", "w");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    srand(time(NULL));
    for (i = 0; i < someNumber; i++) {
        int num = rand() % capNumber;
        int len = sprintf(buffer, "%d\n", num);
        if (len < 0 || len >= sizeof(buffer)) {
            printf("Error: sprintf failed or buffer overflow.\n");
            fclose(fp);
            return 1;
        }
        fputs(buffer, fp);
    }

    fclose(fp);
    printf("testInput10k.txt generated successfully.\n");
    return 0;
}

