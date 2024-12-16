#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

// Structure to hold thread-specific information
struct ThreadInfo {
    char* filename;
    int buffer_size;
    int thread_id;
};

// Function executed by each thread
void* copy_file(void* arg) {
    struct ThreadInfo* thread_info = (struct ThreadInfo*)arg;
    char* filename = thread_info->filename;
    int buffer_size = thread_info->buffer_size;
    int thread_id = thread_info->thread_id;

    char buffer[buffer_size];
    FILE *fp, *cp;
    fp = fopen(filename, "rb");
    if (fp == NULL) {
        perror("Error opening file");
        pthread_exit(NULL);
    }

    char copy_filename[64];
    snprintf(copy_filename, sizeof(copy_filename), "copy_%d_%s", thread_id, filename);
    cp = fopen(copy_filename, "wb");
    if (cp == NULL) {
        perror("Error opening file");
        fclose(fp);
        pthread_exit(NULL);
    }

    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
        fwrite(buffer, 1, bytes, cp);
    }

    fclose(cp);
    fclose(fp);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <filename> <buffer_size> <num_threads>\n", argv[0]);
        return 1;
    }

    char* filename = argv[1];
    int buffer_size = atoi(argv[2]);
    int num_threads = atoi(argv[3]);

    if (num_threads < 2 || num_threads > 64) {
        printf("Number of threads must be between 2 and 64\n");
        return 1;
    }

    pthread_t threads[num_threads];
    struct ThreadInfo thread_info[num_threads];

    // Create threads and assign each thread a different filename
    for (int i = 0; i < num_threads; i++) {
        thread_info[i].filename = filename;
        thread_info[i].buffer_size = buffer_size;
        thread_info[i].thread_id = i;
        if (pthread_create(&threads[i], NULL, copy_file, (void*)&thread_info[i]) != 0) {
            perror("Thread creation failed");
            return 1;
        }
    }

    // Wait for all threads to finish
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}

