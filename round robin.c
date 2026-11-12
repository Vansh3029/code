#include <stdio.h>

int main() {
    int n, i, tq, time = 0;
    int bt[20], rem_bt[20], wt[20], tat[20];
    int total_wt = 0, total_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        printf("Enter burst time of P%d: ", i + 1);
        scanf("%d", &bt[i]);
        rem_bt[i] = bt[i];
    }

    printf("Enter time quantum: ");
    scanf("%d", &tq);

    while(1) {
        int done = 1;

        for(i = 0; i < n; i++) {
            if(rem_bt[i] > 0) {
                done = 0;

                if(rem_bt[i] > tq) {
                    time += tq;
                    rem_bt[i] -= tq;
                }
                else {
                    time += rem_bt[i];
                    wt[i] = time - bt[i];
                    rem_bt[i] = 0;
                }
            }
        }

        if(done == 1)
            break;
    }

    printf("\nProcess\tBT\tWT\tTAT\n");

    for(i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];

        total_wt += wt[i];
        total_tat += tat[i];

        printf("P%d\t%d\t%d\t%d\n",
               i + 1, bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f",
           (float)total_wt / n);

    printf("\nAverage Turnaround Time = %.2f\n",
           (float)total_tat / n);

    return 0;
}
