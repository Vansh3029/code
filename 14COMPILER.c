
#include <stdio.h>
#include <string.h>
#include <ctype.h>
char production[10][10];
int n;

void findFirst(char c)
{
    int i;

    if (!isupper(c))
    {
        printf("%c ", c);
        return;
    }

    for (i = 0; i < n; i++)
    {
        if (production[i][0] == c)
        {
            if (production[i][2] == '#')
                printf("# ");

            else if (!isupper(production[i][2]))
                printf("%c ", production[i][2]);

            else
                findFirst(production[i][2]);
        }
    }
}
int main()
{
    int i;
    char c;

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions (Example: E=aA):\n");

    for (i = 0; i < n; i++)
        scanf("%s", production[i]);

    printf("Enter non-terminal: ");
    scanf(" %c", &c);

    printf("FIRST(%c) = { ", c);
    findFirst(c);
    printf("}\n");

    return 0;
}
