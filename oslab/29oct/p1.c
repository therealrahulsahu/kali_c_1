#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
    int i, status;
    pid_t pid;
    pid=fork();
    if(pid<0)
    {
        printf("\n Process creation faliure\n");
        exit(-1);
    }
    else if(pid>0)
    {
        wait(NULL);
        printf("\nParent starts\n Even Nos.");
        for (i= 2; i <= 10; i+=2)
        {
            printf("")
        }
    }
}