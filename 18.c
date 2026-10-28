#include <stdio.h>

int main()
{
    int block[5] = {100,500,200, 300, 600};
    int process[5] = {212, 417, 112, 426, 150};
    int used[5] = {0};
    int total = 0;

    printf("Process No.\tProcess Size\tBlock No.\tBlock Size\tInternal Fragment\n");

    for (int i = 0; i < 5; i++)
    {
        int allocated = 0;

        for (int j = 0; j < 5; j++)
        {
            if (used[j] == 0 && block[j] >= process[i])
            {
                used[j] = 1;
                total += block[j] - process[i];

                printf("P%d\t\t%d KB\t\t%d\t\t%d KB\t\t%d KB\n",
                       i + 1, process[i], j + 1, block[j],
                       block[j] - process[i]);

                allocated = 1;
                break;
            }
        }

        if (allocated == 0)
        {
            printf("P%d\t\t%d KB\t\tNot Allocated\n",
                   i + 1, process[i]);
        }
    }

    printf("\nTotal internal fragmentation = %d KB\n", total);

    printf("Unused blocks: ");
    for (int i = 0; i < 5; i++)
    {
        if (used[i] == 0)
        {
            printf("B%d (%d KB) ", i + 1, block[i]);
        }
    }

    printf("\n");
    return 0;
}
