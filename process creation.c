
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t n;

    n = fork();

    if(n < 0) {
        printf("Fork failed\n");
        exit(1);
    }

    if(n == 0) {
        printf("Process ID: %d and value of n = %d\n", getpid(), n);
        fflush(stdout);

        execlp("ls", "ls", NULL);

        printf("Exec failed\n");
        exit(1);
    }
    else {
        printf("Process ID: %d and value of n = %d\n", getpid(), n);

        wait(NULL);

        printf("Child completed\n");
    }

    return 0;
}
