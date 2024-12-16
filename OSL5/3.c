#include <stdio.h>
#include <pthread.h>
#include <dispatch/dispatch.h>
#include <unistd.h>

#define BUFFER_SIZE 10
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 2
#define NUM_ITEMS 20

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

dispatch_semaphore_t full, empty;
pthread_mutex_t mutex;

void *producer(void *arg) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        sleep(1); // Production time
        int item = i; // Create Item
        dispatch_semaphore_wait(empty, DISPATCH_TIME_FOREVER); // Wait for empty space
        pthread_mutex_lock(&mutex); // Acquire mutex for buffer access
        buffer[in] = item; // Add Item
        printf("Produced item %d\n", item); // Print Item
        in = (in + 1) % BUFFER_SIZE; // Update index
        pthread_mutex_unlock(&mutex); // Release mutex
        dispatch_semaphore_signal(full); // Signal buffer is full
    }
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        dispatch_semaphore_wait(full, DISPATCH_TIME_FOREVER); // Wait for a full buffer
        pthread_mutex_lock(&mutex); // Acquire mutex for buffer access
        int item = buffer[out]; // Take item
        printf("Consumed item %d\n", item); // Print Item
        out = (out + 1) % BUFFER_SIZE; // Update index
        pthread_mutex_unlock(&mutex); // Release mutex
        dispatch_semaphore_signal(empty); // Signal buffer is empty
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t producers[NUM_PRODUCERS], consumers[NUM_CONSUMERS];
    full = dispatch_semaphore_create(0);
    empty = dispatch_semaphore_create(BUFFER_SIZE);
    pthread_mutex_init(&mutex, NULL);
    for (int i = 0; i < NUM_PRODUCERS; i++) pthread_create(&producers[i], NULL, producer, NULL);
    for (int i = 0; i < NUM_CONSUMERS; i++) pthread_create(&consumers[i], NULL, consumer, NULL);
    for (int i = 0; i < NUM_PRODUCERS; i++) pthread_join(producers[i], NULL);
    for (int i = 0; i < NUM_CONSUMERS; i++) pthread_join(consumers[i], NULL);
    dispatch_release(full);
    dispatch_release(empty);
    pthread_mutex_destroy(&mutex);
    return 0;
}

