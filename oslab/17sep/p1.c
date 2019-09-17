#include <stdio.h>
#include <stdlib.h>
struct gt_node
{
    int pid, st, et;
    struct gt_node *next;
};
struct gt_node *push(struct gt_node *head, int pid, int st, int et)
{
    if(head==NULL)
    {
        struct gt_node *temp = calloc(1, sizeof(struct gt_node));
        temp->pid = pid;
        temp->st = st;
        temp->et = et;
        return temp;
    }
    else
        head->next = push(head->next, pid, st, et);
}
int **input_data(int n)
{
    int **data = calloc(n, sizeof(int*));
    for (int i = 0; i < n; ++i)
        data[i]=calloc(5, sizeof(int));
    // Index-0 to PId
    // Index-1 to AT
    // Index-2 to BT
    // Index-3 to TAT
    // Index-4 to WT
    for(int i=0;i<n;i++)
    {
        data[i][0] = i+1;
        printf("Enter\nAT   for PId %d : ",i+1);
        scanf("%d",&data[i][1]);
        printf("BT   for PId %d : ",i+1);
        scanf("%d",&data[i][2]);
    }
    return data;
}
void output_data(int n, int **data)
{
    for (int i = 0; i < n; ++i)
    {
        printf("PId : %3d  AT : %3d  BT  : %3d  TAT : %3d  WT : %d\n",data[i][0], data[i][1], data[i][2]);
    }
}
void output_seq(int n, int **data)
{
    for (int i = 0; i < n; ++i)
    {
        printf("%d  %c",data[i][0],i==n-1?'\n':'>');
    }
}
int **copy(int n, int **data)
{
    int **temp = calloc(n, sizeof(int*));
    for (int i = 0; i < n; ++i)
        temp[i]=calloc(3, sizeof(int));

    for(int i=0;i<n;i++)
    {
        temp[i][0] = data[i][0];
        temp[i][1] = data[i][1];
        temp[i][2] = data[i][2];
    }

    return temp;
}
void sp2(int *p, int *q)
{
    int temp = *p;
    *p = *q;
    *q = temp;
}
void swap(int *p, int *q)
{
    sp2(p+0,q+0);
    sp2(p+1, q+1);
    sp2(p+2, q+2);
}
int **FCFS(int n, int **data)
{
    int gt=0;
    for (int i = 0; i < n-1; ++i)
    {
        for (int j = i+1; j < n; ++j)
        {
            if(data[i][1]>data[j][1])
                swap(data[i],data[j]);
        }
    }
    int i=0;
    while(1)
    {
        if(gt<data[i][1])
        {
            gt+=data[i][1];
        }

    }
    return data;
}
int **SRTN(int n, int **data)
{
    int time = 0;
    for (int i = 0; i < n-1; ++i)
    {
        for (int j = i+1; j < n; ++j) {
            if(data[i][1]>data[j][1])
                swap(data[i],data[j]);
        }
    }
    return data;
}
int **SJF(int n, int **data)
{
    for (int i = 0; i < n-1; ++i) {
        for (int j = i+1; j < n; ++j) {
            if(data[i][2]>data[j][2])
                swap(data[i],data[j]);
        }
    }
    return data;
}
int main()
{
    int n;
    printf("Enter No. of processes : ");
    scanf("%d",&n);
    int **data = input_data(n);
    printf("\nEntered Seq :\n");
    output_data(n, data);
    printf("\nEntered FCFS :\n");
    output_data(n, FCFS(n, copy(n, data)));
    printf("\nEntered SJF :\n");
    output_data(n, SJF(n, copy(n, data)));
    printf("\nEntered SRTN :\n");
    output_data(n, SRTN(n, copy(n, data)));
}