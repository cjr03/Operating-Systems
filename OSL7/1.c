#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    FILE *fp;
    char buffer[sizeof(int)];
    int i;
    
    if (argc != 3) {
        printf("Usage: %s <someNumber> <capNumber>\n", argv[0]);
        return 1;
    }
    int someNumber = atoi(argv[1]);
    int capNumber = atoi(argv[2]);

    fp = fopen("testInput.txt", "w");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
    
    srand(time(NULL));
    for (i = 0; i < someNumber; i++) {
        sprintf(buffer, "%d\n", rand() % capNumber);
        fputs(buffer, fp);
    }
    
    fclose(fp);
    printf("testInput.txt generated successfully.\n");
    return 0;
}

