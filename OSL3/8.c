#include <stdio.h>

#include <stdlib.h>

#include <pthread.h>

 

void *go(void *);

#define NTHREADS 10

pthread_t threads[NTHREADS];

int main() {
int i;
int *args[NTHREADS];
for (i = 0; i < NTHREADS; i++){
	args[i] = malloc(sizeof(int));
	*args[i] = i;
        pthread_create(&threads[i], NULL, go, args[i]);
}    
for (i = 0; i < NTHREADS; i++) {
	printf("Thread %d returned\n", i);
        pthread_join(threads[i],NULL);
    	free(args[i]);
}
    printf("Main thread done.\n");
    return 0;
}

void *go(void *arg) {
 printf("Hello from thread %d with iteration %d\n",  (int)(unsigned long) pthread_self(), *(int *)arg);
 return 0;
}
