#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
int main()
{
    int sockid=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(sockid==-1)
    {
        perror("socket creation failed\n");
        exit(0);
    }
    struct sockaddr_in server,client;
    server.sin_family=AF_INET;
    server.sin_port=htons(5000);
    server.sin_addr.s_addr=inet_addr("127.0.0.1");
    int c=connect(sockid,(struct sockaddr*)&server,sizeof(server));

    if(c==-1)
    {
        perror("Connect failed\n");
        exit(0);
    }
    int size_buf = 30;
    char str[30];
    while (1)
    {
        printf("Enter Message : ");
        fgets(str, size_buf, stdin);
        send(sockid, str, strlen(str),0);

        int rc=read(sockid,str,sizeof(str));

        if(rc==-1)
        {
            perror("Received Failed\n");
            exit(0);
        }

        printf("Reply : %s\n",str);

    }
    close(sockid);

}
