#include <stdio.h>
void swap(int *, int *);
int main()
{
    int n;
    printf("Enter No. of Process :");
    scanf("%d", &n);
    int pid[n], at[n], bt[n];
    for (int i = 0; i < n; ++i) {
        printf("Enter pid for P[%d] : ", i);
        scanf("%d", &pid[i]);
        printf("Enter at for P[%d] : ", i);
        scanf("%d", &at[i]);
        printf("Enter bt for P[%d] : ", i);
        scanf("%d", &bt[i]);
    }
    // Sorting to be done by at
    for (int i = 0; i < n-1; ++i) {
        for (int j = i; j < n; ++j) {
            if(at[i] > at[j])
            {
                swap(&pid[i], &pid[j]);
                swap(&at[i], &at[j]);
                swap(&bt[i], &bt[j]);
            }
        }
    }
    int tat[n], wt[n];
    for (int i = 0; i < n; ++i) {
        if(i==0)
        {
            wt[i] = 0;
            tat[i] = wt[i] + bt[i];
        } else
        {
            if(at[i] >= at[i-1]+wt[i-1]+bt[i-1])
            {
                wt[i] = 0;
                tat[i] = wt[i] + bt[i];
            } else
            {
                wt[i] = at[i-1]+wt[i-1]+bt[i-1]-at[i];
                tat[i] = wt[i]+bt[i];
            }
        }
    }
    float av_wt = 0, av_tat=0;
    for (int i = 0; i < n; ++i) {
        av_tat+=(float)tat[i];
        av_wt+=(float)wt[i];
    }
    printf("Average \nWT : %f\nTAT : %f\n", av_wt/n, av_tat/n);
}
void  swap(int *p, int *q)
{
    int temp = *p;
    *p = *q;
    *q = temp;
}
