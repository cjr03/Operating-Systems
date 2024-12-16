#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_CACHE_SIZE 1000

typedef struct {
    int page_num;
} Page;

int pageFaults(int cacheSize) {
    Page *cache = (Page *)malloc(cacheSize * sizeof(Page));
    int page_faults = 0;
    int head = 0; // Pointer to the oldest page in the cache

    for (int i = 0; i < cacheSize; i++) {
        cache[i].page_num = -1; // Initialize page numbers to -1 (invalid)
    }

    char pageCache[100];

    while (fgets(pageCache, 100, stdin)) {
        int page_num = atoi(pageCache);

        bool found = false;
        for (int i = 0; i < cacheSize; i++) {
            if (cache[i].page_num == page_num) {
                found = true;
                break;
            }
        }

        if (!found) {
            // Replace the oldest page with the new page
            cache[head].page_num = page_num;
            head = (head + 1) % cacheSize; // Move head to the next position
            page_faults++;
            printf("%d\n", page_num); // Print the page number that caused the page fault
        }
    }

    free(cache);

    return page_faults;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <cache size>\n", argv[0]);
        return 1;
    }

    int cacheSize = atoi(argv[1]);
    printf("Total page faults: %d\n", pageFaults(cacheSize));
    return 0;
}

