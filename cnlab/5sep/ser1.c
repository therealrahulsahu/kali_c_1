#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdlib.h>
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
    int b=bind(sockid,(struct sockaddr*)&server,sizeof(server));

    if(b==-1)
    {
        perror("bind failed\n");
        exit(0);
    }

    listen(sockid,5);
    int size=sizeof(struct sockaddr);
    int newfd=accept(sockid,(struct sockaddr*)&client,&size);

    if(newfd==-1)
    {
        perror("Accept Failed\n");
        exit(0);
    }

    char *data=(char *)malloc(200* sizeof(char));
    int rc=recv(newfd,data,200* sizeof(char),0);

    if(rc==-1)
    {
        perror("Reciving Failed\n");
        exit(0);
    }
    data[rc]='\0';
    close(sockid);
    close(newfd);


    //int len = strlen(data);
    printf("%s\n",data);
    FILE *fp=fopen("datarecv.txt","w");
    if(fp==NULL)
    {
        perror("File Not Found!!!\n");
        exit(1);
    }
    fwrite(data,1,rc,fp);
    printf("Done!!!!\n");
}