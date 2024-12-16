#include <stdio.h>
#include <stdlib.h>

int main() {
    char pageCache[100];

    while (fgets(pageCache, 100, stdin)) {
        int page_num = atoi(pageCache);
        printf("Received page request: %d\n", page_num);
    }

    printf("End of file reached. Simulation terminated.\n");

    return 0;
}

