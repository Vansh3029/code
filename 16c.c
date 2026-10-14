
#include <stdio.h>
#define P 5
#define R 3

int available[R] = {3, 3, 2};
int allocation[P][R] = {{0,1,0},{2,0,0},{3,0,2},{2,1,1},{0,0,2}};
int max[P][R] = {{7,5,3},{3,2,2},{9,0,2},{2,2,2},{4,3,3}};
int need[P][R];

void calculate_need()
{
    for(int i=0;i<P;i++)
        for(int j=0;j<R;j++)
            need[i][j]=max[i][j]-allocation[i][j];
}

void print_need()
{
    printf("\nNeed Matrix:\n     A  B  C\n");
    for(int i=0;i<P;i++) {
        printf("P%d   ",i);
        for(int j=0;j<R;j++)
            printf("%d  ",need[i][j]);
        printf("\n");
    }
}

int is_safe()
{
    int work[R],finish[P]={0},safe_sequence[P],count=0;
    for(int j=0;j<R;j++)
        work[j]=available[j];

    while(count<P) {
        int found=0;
        for(int i=0;i<P;i++) {
            if(finish[i]==0) {
                int possible=1;
                for(int j=0;j<R;j++)
                    if(need[i][j]>work[j]) {
                        possible=0;
                        break;
                    }
                if(possible) {
                    for(int j=0;j<R;j++)
                        work[j]+=allocation[i][j];
                    finish[i]=1;
                    safe_sequence[count++]=i;
                    found=1;
                }
            }
        }
        if(found==0)
            break;
    }

    if(count==P) {
        printf("System is in a SAFE state.\nSafe Sequence: ");
        for(int i=0;i<P;i++) {
            printf("P%d",safe_sequence[i]);
            if(i<P-1)
                printf(" -> ");
        }
        printf("\n");
        return 1;
    }
    printf("System is in an UNSAFE state.\n");
    return 0;
}

void request(int p,int req[])
{
    printf("\nRequest by P%d: (%d, %d, %d)\n",p,req[0],req[1],req[2]);

    for(int j=0;j<R;j++)
        if(req[j]>need[p][j]) {
            printf("Error: Process has exceeded its maximum claim.\n");
            return;
        }

    for(int j=0;j<R;j++)
        if(req[j]>available[j]) {
            printf("Resources not available. P%d must WAIT.\n",p);
            return;
        }

    for(int j=0;j<R;j++) {
        available[j]-=req[j];
        allocation[p][j]+=req[j];
        need[p][j]-=req[j];
    }

    if(is_safe())
        printf("Request GRANTED.\n");
    else {
        for(int j=0;j<R;j++) {
            available[j]+=req[j];
            allocation[p][j]-=req[j];
            need[p][j]+=req[j];
        }
        printf("Request would lead to an UNSAFE state. Request DENIED (rolled back).\n");
    }
}

int main()
{
    int req1[R]={1,0,2},req2[R]={3,3,0},req3[R]={0,2,0};
    calculate_need();
    print_need();
    printf("\nInitial Safety Check:\n");
    is_safe();
    request(1,req1);
    request(4,req2);
    request(0,req3);
    return 0;
}
