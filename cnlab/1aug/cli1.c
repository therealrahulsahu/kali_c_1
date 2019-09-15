#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h> 
  
#define PORT  9000

int main() { 
    int sockfd;
    struct sockaddr_in  servaddr;

    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 )
    {
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
  
    memset(&servaddr, 0, sizeof(servaddr)); 

    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
      
    int n, len; 

    printf("Enter a No. : ");
    int data;
    scanf("%d", &data);
    int *var=&data;

    sendto(sockfd, (int *)var, sizeof(var), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));


    n = recvfrom(sockfd, (int *)var, sizeof(var), MSG_WAITALL, (struct sockaddr *) &servaddr, &len);

    if(*var)
        printf("Armstrong .....\n");
    else
        printf("Not Armstrong\n");
    close(sockfd); 
    return 0; 
} 
