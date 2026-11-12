#include <stdio.h>

struct P {
    int id, at, bt, ct, tat, wt;
};

int main() {
    int n, t = 0, done[100] = {0}, count = 0;
    float tat = 0, wt = 0;
    struct P p[100];

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        scanf("%d%d", &p[i].at, &p[i].bt);
    }

    while (count < n) {
        int k = -1;

        for (int i = 0; i < n; i++)
            if (!done[i] && p[i].at <= t &&
               (k == -1 || p[i].bt < p[k].bt))
                k = i;

        if (k == -1) {
            t++;
            continue;
        }

        t += p[k].bt;
        p[k].ct = t;
        p[k].tat = t - p[k].at;
        p[k].wt = p[k].tat - p[k].bt;

        tat += p[k].tat;
        wt += p[k].wt;
        done[k] = 1;
        count++;
    }

    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
        p[i].id, p[i].at, p[i].bt, p[i].ct,
        p[i].tat, p[i].wt);

    printf("ATAT = %.2f\n", tat / n);
    printf("AWT = %.2f\n", wt / n);

    return 0;
}