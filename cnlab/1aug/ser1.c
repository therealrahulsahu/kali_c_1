#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
  
#define PORT  9000
int checkarmstrong(int number)
{
    int originalNumber, remainder, result = 0;

    originalNumber = number;
    while (originalNumber != 0)
    {
        remainder = originalNumber%10;
        result += remainder*remainder*remainder;
        originalNumber /= 10;
    }
    if(result == number)
        return 1;
    else
        return 0;
}

int main()
{
    int sockfd;
    struct sockaddr_in servaddr, cliaddr; 

    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
      
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT); 
      
    if ( bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 )
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 


    int len, n;
    int *var;
    n = recvfrom(sockfd, (int *) var, sizeof(int), MSG_WAITALL, (struct sockaddr *) &cliaddr, &len);

    printf("Entered No. %d\n", *var);

    *var = checkarmstrong(*var);
    sendto(sockfd, (int *)var, sizeof(int), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len);

        printf("Done!!!!!\n");

    return 0; 
} 
