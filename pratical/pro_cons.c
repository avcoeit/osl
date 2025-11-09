#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SIZE 5   // Buffer size

int buffer[SIZE];
int in = 0, out = 0;

sem_t emptySlots;   // Counts empty spaces in buffer
sem_t fullSlots;    // Counts filled spaces in buffer
pthread_mutex_t lock;

void *producer(void *arg) {
    for (int i = 0; i < 10; i++) {
        int item = rand() % 100;   // Produce item

        sem_wait(&emptySlots);     // Wait if buffer is full
        pthread_mutex_lock(&lock);

        buffer[in] = item;
        printf("Producer produced: %d\n", item);
        in = (in + 1) % SIZE;

        pthread_mutex_unlock(&lock);
        sem_post(&fullSlots);      // Increase filled slot count
        sleep(1);
    }
    return NULL;
}

void *consumer(void *arg) {
    for (int i = 0; i < 10; i++) {

        sem_wait(&fullSlots);      // Wait if buffer is empty
        pthread_mutex_lock(&lock);

        int item = buffer[out];
        printf("Consumer consumed: %d\n", item);
        out = (out + 1) % SIZE;

        pthread_mutex_unlock(&lock);
        sem_post(&emptySlots);     // Increase empty slot count
        sleep(2);
    }
    return NULL;
}

int main() {
    pthread_t prodThread, consThread;

    sem_init(&emptySlots, 0, SIZE); // Initially buffer is empty
    sem_init(&fullSlots, 0, 0);     // No items yet
    pthread_mutex_init(&lock, NULL);

    pthread_create(&prodThread, NULL, producer, NULL);
    pthread_create(&consThread, NULL, consumer, NULL);

    pthread_join(prodThread, NULL);
    pthread_join(consThread, NULL);

    sem_destroy(&emptySlots);
    sem_destroy(&fullSlots);
    pthread_mutex_destroy(&lock);

    return 0;
}
// sagar@sagar-Lenovo-V15-IIL:~/Pictures/osl$ gcc pro_cons.c
//sagar@sagar-Lenovo-V15-IIL:~/Pictures/osl$ ./a.out

