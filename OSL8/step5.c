#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void* copy_file(void* arg) {
    char* filename = (char*)arg;
    FILE* fp = fopen(filename, "rb");
    if (fp == NULL) {
        perror("Error opening file");
        pthread_exit(NULL);
    }

    char copy_filename[50];
    strcpy(copy_filename, "copy_");
    strcat(copy_filename, filename);
    FILE* cp = fopen(copy_filename, "wb");
    if (cp == NULL) {
        perror("Error opening file");
        fclose(fp);
        pthread_exit(NULL);
    }

    char buffer[atoi(argv[2])];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
        fwrite(buffer, 1, bytes, cp);
    }

    fclose(cp);
    fclose(fp);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {

    int num_threads = atoi(argv[3]) % 8;
    pthread_t threads[num_threads];

    for (int i = 0; i < num_threads + 1; i++) {
        if (pthread_create(&threads[i], NULL, copy_file, argv[1]) != 0) {
            perror("Thread creation failed");
            return 1;
        }
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
