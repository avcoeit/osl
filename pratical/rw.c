#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t writeLock = PTHREAD_MUTEX_INITIALIZER;
int readCount = 0;

void* reader(void* arg) {
    pthread_mutex_lock(&mutex);
    readCount++;
    if (readCount == 1)
        pthread_mutex_lock(&writeLock);   // First reader blocks writer
    pthread_mutex_unlock(&mutex);

    printf("Reader %ld is reading\n", (long)arg);
    sleep(1);

    pthread_mutex_lock(&mutex);
    readCount--;
    if (readCount == 0)
        pthread_mutex_unlock(&writeLock); // Last reader allows writer
    pthread_mutex_unlock(&mutex);

    printf("Reader %ld left\n", (long)arg);
    return NULL;
}

void* writer(void* arg) {
    pthread_mutex_lock(&writeLock);
    printf("Writer %ld is writing\n", (long)arg);
    sleep(2);
    pthread_mutex_unlock(&writeLock);
    printf("Writer %ld left\n", (long)arg);
    return NULL;
}

int main() {
    int r, w;
    printf("Enter number of readers: ");
    scanf("%d", &r);
    printf("Enter number of writers: ");
    scanf("%d", &w);

    pthread_t rt[r], wt[w];

    for (long i = 0; i < r; i++)
        pthread_create(&rt[i], NULL, reader, (void*)i);

    for (long i = 0; i < w; i++)
        pthread_create(&wt[i], NULL, writer, (void*)i);

    for (int i = 0; i < r; i++)
        pthread_join(rt[i], NULL);
    for (int i = 0; i < w; i++)
        pthread_join(wt[i], NULL);

    return 0;
}

