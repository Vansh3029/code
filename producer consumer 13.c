#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define N 5

int buffer[N];
int in = 0;
int out = 0;

sem_t empty;
sem_t full;
sem_t mutex;

void *producer(void *arg)
{
    for (int i = 1; i <= 10; i++)
    {
        int item = rand() % 100;

        sem_wait(&empty);
        sem_wait(&mutex);

        int index = in;
        buffer[in] = item;
        in = (in + 1) % N;
        printf("%d producer produce %d at %d\n", i, item, index);
        sem_post(&full);
        sem_post(&mutex);

        
    }

    return NULL;
}

void *consumer(void *arg)
{
    for (int i = 1; i <= 10; i++)
    {
        sem_wait(&full);
        sem_wait(&mutex);

        int index = out;
        int item = buffer[out];
        out = (out + 1) % N;
        printf("%d consumer consume %d from %d\n", i, item, index);
        sem_post(&empty);
        sem_post(&mutex);

        
    }

    return NULL;
}

int main()
{
    pthread_t producerThread, consumerThread;

    srand(time(NULL));

    sem_init(&empty, 0, N);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    pthread_create(&producerThread, NULL, producer, NULL);
    pthread_create(&consumerThread, NULL, consumer, NULL);

    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}