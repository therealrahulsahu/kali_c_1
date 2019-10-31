#include <stdio.h>
#include <sys/types.h>
#define STDIN 1

int main()
{
    char ch;
    fd_set readfd;
    FD_ZERO(&readfd);
    FD_SET(STDIN, &readfd);

    struct timeval tm;
    tm.tv_sec=5;
    int ret_id = select(2, &readfd, NULL, NULL, &tm);
    if(ret_id==0)
    {
        printf("Timeout Occurred\n");
    }
    else if(ret_id==-1)
    {
        printf("Error\n");
    }
    if(FD_ISSET(1,&readfd))
    {
        scanf("%c", &ch);
        printf("Key is pressed %c\n", ch);
    }

}