#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
struct student
{
    char *name;
    int roll;
    float grade;
};
struct student *input_data()
{
    struct student *temp = (struct student *)malloc(sizeof(struct student));
    printf("Enter name : ");
    scanf("%s", temp->name);
    printf("Enter Roll No. :");
    scanf("%s")
}
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




    close(sockid);
    close(newfd);
}

