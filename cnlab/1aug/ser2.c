#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT  9000
struct student
{
    int roll;
    char *name;
    int m1, m2 , m3;
    int avg;
    int total;
};

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
    struct student *var = (struct student *)malloc(sizeof(struct student));
    n = recvfrom(sockfd, (struct student *) var, sizeof(struct student), MSG_WAITALL, (struct sockaddr *) &cliaddr, &len);

    var->total = var->m1 + var->m2 + var->m3;
    var->avg = var->total/3;

    sendto(sockfd, (struct student *)var, sizeof(struct student), MSG_CONFIRM, (struct sockaddr *) &cliaddr, len);

    printf("Done!!!!!\n");

    return 0;
}
