#include <stdio.h>

struct P {
    int id, at, bt, ct, tat, wt;
};

void swap(struct P *a, struct P *b) {
    struct P t = *a;
    *a = *b;
    *b = t;
}

int main() {
    int n, t = 0;
    float tat = 0, wt = 0;
    struct P p[100];

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        scanf("%d%d", &p[i].at, &p[i].bt);
    }

    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (p[i].at > p[j].at)
                swap(&p[i], &p[j]);

    for (int i = 0; i < n; i++) {
        if (t < p[i].at)
            t = p[i].at;

        t += p[i].bt;
        p[i].ct = t;
        p[i].tat = t - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        tat += p[i].tat;
        wt += p[i].wt;
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