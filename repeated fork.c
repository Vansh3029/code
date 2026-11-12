#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t root = getpid();
    pid_t child[3];
    int count = 0;

    for(int i = 0; i < 3; i++) {
        pid_t n = fork();

        if(n == 0) {
            continue;
        }
        else if(n > 0) {
            child[count++] = n;
        }
        else {
            printf("Fork failed\n");
            return 1;
        }
    }

    printf("Process ID: %d, Parent ID: %d\n", getpid(), getppid());
    fflush(stdout);

    for(int i = 0; i < count; i++) {
        waitpid(child[i], NULL, 0);
    }

    if(getpid() == root) {
        printf("Total number of processes created = 8 (2^3)\n");
    }

    return 0;
}
