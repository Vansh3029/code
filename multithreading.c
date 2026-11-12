#include <stdio.h>
#include <pthread.h>

void *even(void *arg) {
    for (int i = 2; i <= 20; i += 2) {
        printf("Thread 1 (even): %d\n", i);
    }
    return NULL;
}

void *odd(void *arg) {
    for (int i = 1; i <= 19; i += 2) {
        printf("Thread 2 (odd): %d\n", i);
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, even, NULL);
    pthread_create(&thread2, NULL, odd, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    printf("both threads have finished execution\n");
    return 0;
}