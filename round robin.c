#include <stdio.h>

struct Process {
    int pid;
    int at;
    int bt;
    int rt;
    int ct;
    int tat;
    int wt;
};

int main() {
    int n, tq;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;

        printf("\nProcess P%d\n", i + 1);

        printf("Arrival Time: ");
        scanf("%d", &p[i].at);

        printf("Burst Time: ");
        scanf("%d", &p[i].bt);

        p[i].rt = p[i].bt;
    }

    printf("\nEnter Time Quantum: ");
    scanf("%d", &tq);

    int completed = 0;
    int time = 0;
    int queue[n * 100];
    int front = 0, rear = 0;
    int visited[n];

    for (int i = 0; i < n; i++)
        visited[i] = 0;

    while (completed < n) {

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rt > 0 && visited[i] == 0) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        if (front == rear) {
            time++;
            continue;
        }

        int index = queue[front++];

        int execute;

        if (p[index].rt < tq)
            execute = p[index].rt;
        else
            execute = tq;

        p[index].rt -= execute;
        time += execute;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rt > 0 && visited[i] == 0) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        if (p[index].rt > 0) {
            queue[rear++] = index;
        } else {
            p[index].ct = time;
            p[index].tat = p[index].ct - p[index].at;
            p[index].wt = p[index].tat - p[index].bt;
            completed++;
        }
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    printf("---------------------------------------------\n");

    float totalWT = 0, totalTAT = 0;

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].at,
               p[i].bt,
               p[i].ct,
               p[i].tat,
               p[i].wt);

        totalWT += p[i].wt;
        totalTAT += p[i].tat;
    }

    printf("\nAverage Waiting Time = %.2f", totalWT / n);
    printf("\nAverage Turnaround Time = %.2f\n", totalTAT / n);

    return 0;
}