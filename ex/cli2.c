#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

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
    servaddr.sin_port = htons(9000);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int len;

    char filename[20];
    printf("Enter Filename : ");
    scanf("%s", filename);

    int snd = sendto(sockfd, filename, strlen(filename), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
    if(snd<0)
    {
        perror("Sending failed\n");
        exit(-1);
    }

    char content[500];
    int rc = recvfrom(sockfd, content, 500, MSG_WAITALL, (struct sockaddr *) &servaddr, &len);
    if(rc<0)
    {
        perror("Receive failed\n");
        exit(-1);
    }
    printf("Content :\v%s", content);

    close(sockfd);
    return 0;
}
