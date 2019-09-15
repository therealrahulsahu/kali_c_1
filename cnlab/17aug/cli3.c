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
    char name[20];
    int roll;
    float grade;
};
struct student *input_data()
{
    struct student *temp = calloc(1, sizeof(struct student));
    printf("Enter name : ");
    scanf("%s", temp->name);
    printf("Enter Roll No. :");
    scanf("%d",&(temp->roll));
    printf("Enter grade : ");
    scanf("%f",&(temp->grade));
    return temp;
}
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

    struct student *data=input_data();

    int sd = send(sockid, data,sizeof(struct student),0);
    if(sd<0)
    {
        perror("Sending Failed\n");
        exit(0);
    }

    close(sockid);
}
