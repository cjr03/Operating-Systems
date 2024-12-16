#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 10
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 2
#define NUM_ITEMS 20

int buffer[BUFFER_SIZE];
int in = 0, out = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;

void *producer(void *arg) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        sleep(1); // Production time
        int item = i; // Make item
        pthread_mutex_lock(&mutex); // Lock mutex
        while (in == BUFFER_SIZE) pthread_cond_wait(&empty, &mutex); // Buffer full, wait for buffer to become empty
        buffer[in] = item; // Add item
        printf("Produced item %d\n", item); // Print item
        in = (in + 1) % BUFFER_SIZE; // Update buffer
        pthread_cond_signal(&full); // Signal full buffer
        pthread_mutex_unlock(&mutex); // Unlock mutex
    }
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        pthread_mutex_lock(&mutex); // Lock mutex
        while (out == in) pthread_cond_wait(&full, &mutex); // Buffer is empty, wait for full buffer
        int item = buffer[out]; // Get item
        out = (out + 1) % BUFFER_SIZE; // Update index
        pthread_cond_signal(&empty); // Signal empty buffer
        pthread_mutex_unlock(&mutex); // Unlock mutex
        printf("Consumed item %d\n", item); // Print item
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t producers[NUM_PRODUCERS], consumers[NUM_CONSUMERS];
    for (int i = 0; i < NUM_PRODUCERS; i++) pthread_create(&producers[i], NULL, producer, NULL);
    for (int i = 0; i < NUM_CONSUMERS; i++) pthread_create(&consumers[i], NULL, consumer, NULL);
    for (int i = 0; i < NUM_PRODUCERS; i++) pthread_join(producers[i], NULL);
    for (int i = 0; i < NUM_CONSUMERS; i++) pthread_join(consumers[i], NULL);
    return 0;
}

