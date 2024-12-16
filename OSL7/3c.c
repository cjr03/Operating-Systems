#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_CACHE_SIZE 1000

typedef struct {
    int page_num;
    bool referenced;
} Page;

int pageFaults(int cacheSize) {
    Page *cache = (Page *)malloc(cacheSize * sizeof(Page));
    int page_faults = 0;
    int clock_hand = 0;

    for (int i = 0; i < cacheSize; i++) {
        cache[i].page_num = -1;
        cache[i].referenced = false;
    }

    char pageCache[100];

    while (fgets(pageCache, 100, stdin)) {
        int page_num = atoi(pageCache);

        bool found = false;
        for (int i = 0; i < cacheSize; i++) {
            if (cache[i].page_num == page_num) {
                cache[i].referenced = true;
                found = true;
                break;
            }
        }

        if (!found) {
            while (true) {
                if (!cache[clock_hand].referenced) {
                    cache[clock_hand].page_num = page_num;
                    cache[clock_hand].referenced = true;
                    clock_hand = (clock_hand + 1) % cacheSize;
                    page_faults++;
                    printf("%d\n", page_num);
                    break;
                } else {
                    cache[clock_hand].referenced = false;
                    clock_hand = (clock_hand + 1) % cacheSize;
                }
            }
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

