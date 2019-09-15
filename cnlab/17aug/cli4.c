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
    struct sockaddr_in server;
    server.sin_family=AF_INET;
    server.sin_port=htons(5000);
    server.sin_addr.s_addr=inet_addr("127.0.0.1");
    int c=connect(sockid,(struct sockaddr*)&server,sizeof(server));

    if(c==-1)
    {
        perror("Connect failed\n");
        exit(0);
    }

    char *str="Welcome to Kiit \0";
    printf("Sending... %s\n",str);

    int k=send(sockid, str, strlen(str), 0);

    if(k==-1)
    {
        perror("Sendind Failed\n");
        exit(0);
    }

    int rc=read(sockid,str,20);

    if(rc==-1)
    {
        perror("Received Failed\n");
        exit(0);
    }
    str[rc]='\0';

    printf("Message from server is %s\n",str);
    close(sockid);
}
