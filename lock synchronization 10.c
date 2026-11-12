
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int lock = 0;
int shared_data = 0;
int inside = 0;

void acquire_lock(){
    while(lock == 1)
    lock = 1;
}

void release_lock(){
    lock = 0;
}

void *process(void *arg){
    int id = *(int *)arg;
    printf("Thread %d waiting for lock...\n", id);
    acquire_lock();
    inside++;
    printf("Thread %d ENTERED critical section\n", id);
    if(inside > 1) {
        printf("Error: More than one thread in critical section!\n");
    }
    int temp = shared_data;
    shared_data = temp + 1;
    printf("Thread %d EXITED critical section\n", id);
    inside--;
    release_lock();
    return NULL;
}

int main(){
    pthread_t threads[3];
    int id[3] = {1, 2, 3};

    for (int i = 0; i < 3; i++)
        pthread_create(&threads[i], NULL, process, &id[i]);

    for (int i = 0; i < 3; i++)
        pthread_join(threads[i], NULL);

    printf("\nFinal shared data = %d\n", shared_data);

    return 0;
}