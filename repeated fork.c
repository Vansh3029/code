#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t root = getpid();
    int count = 1;

    for (int i = 0; i < 3; i++) {
        fork();
        count *= 2;
    }

    printf("PID: %d, PPID: %d\n", getpid(), getppid());

    while (wait(NULL) > 0);

    if (getpid() == root)
        printf("Total processes = %d (2^3)\n", count);

    return 0;
}