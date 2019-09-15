#include <stdlib.h>
#include <stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include <string.h>
int main()
{
    char *data = (char *)malloc(200* sizeof(char));
    FILE *fp=fopen("datasend.txt","r");
    if(fp==NULL)
    {
        perror("File Not Found!!!\n");
        exit(1);
    }
    fread(data,1,200,fp);
    //printf("%s",data);
    //printf("\n");
    //printf("%d",strlen(data));
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

    int k=send(sockid, data, strlen(data), 0);

    if(k==-1)
    {
        perror("Sending Failed\n");
        exit(0);
    }

    close(sockid);
}