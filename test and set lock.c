#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int lock = 0;
int shared_data = 0;

int test_and_set(int *lock)
{
    return __sync_lock_test_and_set(lock, 1);
}

void acquire_lock()
{
    while (test_and_set(&lock) == 1)
        usleep(1000);
}

void release_lock()
{
    __sync_lock_release(&lock);
}

void *process(void *arg)
{
    int id = *(int *)arg;

    printf("Thread %d waiting for lock...\n", id);

    acquire_lock();

    printf("Thread %d ENTERED critical section\n", id);

    int temp = shared_data;
    sleep(1);
    shared_data = temp + 1;

    printf("Thread %d EXITED critical section\n", id);

    release_lock();

    return NULL;
}

int main()
{
    pthread_t threads[3];
    int id[3] = {1, 2, 3};

    for (int i = 0; i < 3; i++)
        pthread_create(&threads[i], NULL, process, &id[i]);

    for (int i = 0; i < 3; i++)
        pthread_join(threads[i], NULL);

    printf("\nFinal shared data = %d\n", shared_data);

    return 0;
}