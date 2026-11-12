#include <stdio.h>

int main() {
    int ref[] = {4, 7, 6, 1, 7, 6, 1, 2, 7, 2,
                 6, 3, 1, 7, 4, 2, 6, 1, 3, 7};

    int n = 20, frame[3] = {-1, -1, -1};
    int faults = 0, hits = 0;

    printf("Ref No.\tPage\tF1\tF2\tF3\tStatus\n");

    for (int i = 0; i < n; i++) {
        int page = ref[i], found = 0;

        for (int j = 0; j < 3; j++) {
            if (frame[j] == page) {
                found = 1;
                break;
            }
        }

        if (found) {
            hits++;
        } else {
            faults++;
            int pos = -1;

            for (int j = 0; j < 3; j++) {
                if (frame[j] == -1) {
                    pos = j;
                    break;
                }
            }

            if (pos == -1) {
                int farthest = -1;

                for (int j = 0; j < 3; j++) {
                    int k;

                    for (k = i + 1; k < n; k++) {
                        if (frame[j] == ref[k])
                            break;
                    }

                    if (k > farthest) {
                        farthest = k;
                        pos = j;
                    }
                }
            }

            frame[pos] = page;
        }

        printf("%d\t%d\t", i + 1, page);

        for (int j = 0; j < 3; j++) {
            if (frame[j] == -1)
                printf("-\t");
            else
                printf("%d\t", frame[j]);
        }

        printf("%s\n", found ? "Hit" : "Fault");
    }

    printf("\nTotal page faults = %d\n", faults);
    printf("Total page hits = %d\n", hits);
    printf("Hit ratio = %.2f%%\n", (hits * 100.0) / n);
    printf("Fault ratio = %.2f%%\n", (faults * 100.0) / n);

    return 0;
}