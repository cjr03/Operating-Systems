#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_CACHE_SIZE 1000

typedef struct {
    int page_num;
    int last_used; // Keeps track of when the page was last used
} Page;

int pageFaults(int cacheSize) {
    Page *cache = (Page *)malloc(cacheSize * sizeof(Page));
    int page_faults = 0;
    int current_time = 0;

    for (int i = 0; i < cacheSize; i++) {
        cache[i].page_num = -1;
        cache[i].last_used = 0;
    }

    char pageCache[100];

    while (fgets(pageCache, 100, stdin)) {
        int page_num = atoi(pageCache);

        bool found = false;
        int least_recently_used_index = 0;
        int least_recent_time = current_time;

        // Check if the page is already in cache and find the least recently used page
        for (int i = 0; i < cacheSize; i++) {
            if (cache[i].page_num == page_num) {
                cache[i].last_used = current_time;
                found = true;
                break;
            }
            if (cache[i].last_used < least_recent_time) {
                least_recent_time = cache[i].last_used;
                least_recently_used_index = i;
            }
        }

        if (!found) {
            cache[least_recently_used_index].page_num = page_num;
            cache[least_recently_used_index].last_used = current_time;
            page_faults++;
            printf("%d\n", page_num);
        }

        current_time++;
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

