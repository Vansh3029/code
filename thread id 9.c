#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *func(void *arg){
    int n = *(int *)arg;
    pthread_t id = pthread_self();
    printf("Thread %d: my ID is %lu\n", n, (unsigned long)id);
    free(arg);
    return NULL;
}

int main(){
    int n;
    scanf("%d", &n);
    pthread_t threads[n];
    for(int i=0; i<n; i++){
        int *arg = malloc(sizeof(int));
        *arg = i;
        pthread_create(&threads[i], NULL, func, arg);
    }
    for(int i=0; i<n; i++){
        pthread_join(threads[i], NULL);
    }
    if(pthread_equal(threads[0], threads[1]))
        printf("Same threads\n");
    else
        printf("Different threads\n");
    printf("All %d threads have completed.\n", n);
    return 0;
}