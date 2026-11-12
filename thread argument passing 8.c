#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void* fact(void *arg){
    int n = *(int *)arg;
    int *ans = malloc(sizeof(int));
    *ans = 1;
    for(int i=1; i<=n; i++) *ans *= i;
    free(arg);
    pthread_exit(ans);
}

int main(){
    pthread_t threads[5];
    for(int i=0; i<5; i++){
        int *arg = malloc(sizeof(int));
        *arg = i+1;
        pthread_create(&threads[i], NULL, fact, arg);
    }
    for(int i = 0; i < 5; i++) {
        void *ans;
        pthread_join(threads[i], &ans);
        printf("Thread for n=%d computed factorial: %d\n", i+1, *(int *)ans);
        free(ans);
    }
    printf("All threads have returned their results.\n");
    return 0;
}