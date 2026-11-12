#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
sem_t s0;
sem_t s1;
void * p1(void * arg)
{
    for(int i=0;i<5;i++)
    {sem_wait(&s0);
    printf("0");
    sem_post(&s1);}
}
void * p2(void * arg)
{
    for(int i=0;i<5;i++)
    {sem_wait(&s1);
    printf("1");
    sem_post(&s0);}
}
int main()
{
    sem_init(&s0,0,1);
    sem_init(&s1,0,0);
    pthread_t t1,t2;
    pthread_create(&t1,NULL,p1,NULL);
    pthread_create(&t2,NULL,p2,NULL);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    sem_destroy(&s0);
    sem_destroy(&s1);
    return 0;
}