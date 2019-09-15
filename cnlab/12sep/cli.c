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

    while (1)
    {
        char *data = (char *) malloc(100 * sizeof(char));
        printf("Enter Message and 0 to end : ");
        scanf("%s", data);
        int k = send(sockid, data, strlen(data), 0);
        if (k == -1)
        {
            perror("Sending Failed\n");
            exit(0);
        }
        if(data[0]=='0')
            break;
        printf("Sending Done!\n");
        int rc = recv(sockid, data, 200 * sizeof(char), 0);
        if (rc == -1)
        {
            perror("Recieving Failed\n");
            exit(0);
        }
        data[rc]='\0';
        printf("From Server : %s\n",data);
    }
    close(sockid);
}