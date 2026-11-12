#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define N 2
#define TRUE 1
#define FALSE 0

int shareData = 0;
int interested[N] = {FALSE, FALSE};
int turn;
int count = 0;

void entry(int process)
{
    int other = 1 - process;

    interested[process] = TRUE;
    turn = other;

    while (interested[other] == TRUE && turn == other);
}

void exit_section(int process)
{
    interested[process] = FALSE;
}

void *critical_section(void *arg)
{
    int id = *(int *)arg;

    while (1)
    {
        entry(id);

        if (count > 10)
        {
            exit_section(id);
            break;
        }

        printf("Thread %d enter CS, share Data = %d\n", id, shareData);

        usleep(100000);

        shareData++;

        printf("Thread %d exit CS, share Data = %d\n", id, shareData);

        count++;

        exit_section(id);
    }

    return NULL;
}

int main()
{
    pthread_t thread[2];
    int id[2] = {0, 1};

    pthread_create(&thread[0], NULL, critical_section, &id[0]);
    pthread_create(&thread[1], NULL, critical_section, &id[1]);

    pthread_join(thread[0], NULL);
    pthread_join(thread[1], NULL);

    printf("\nFinal shareData = %d\n", shareData);

    return 0;
}
