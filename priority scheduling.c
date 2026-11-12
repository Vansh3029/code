#include <stdio.h>

struct Process {
    int pid;
    int at;
    int bt;
    int rt;
    int priority;
    int ct;
    int tat;
    int wt;
};

int main() {
    int n;
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

        printf("Priority: ");
        scanf("%d", &p[i].priority);

        p[i].rt = p[i].bt;
    }

    int completed = 0;
    int time = 0;

    while (completed < n) {
        int index = -1;
        int highestPriority = -1;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rt > 0) {
                if (p[i].priority > highestPriority) {
                    highestPriority = p[i].priority;
                    index = i;
                }
            }
        }

        if (index == -1) {
            time++;
            continue;
        }

        p[index].rt--;
        time++;

        if (p[index].rt == 0) {
            p[index].ct = time;
            p[index].tat = p[index].ct - p[index].at;
            p[index].wt = p[index].tat - p[index].bt;
            completed++;
        }
    }

    printf("\nPID\tAT\tBT\tPriority\tCT\tTAT\tWT\n");

    float totalWT = 0, totalTAT = 0;

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].at,
               p[i].bt,
               p[i].priority,
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