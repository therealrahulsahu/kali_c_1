#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

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
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(9000);

    if ( bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }


    int len;
    int filename[20];
    int rc = recvfrom(sockfd, filename, 20, MSG_WAITALL, (struct sockaddr *) &cliaddr, &len);
    if(rc<0)
    {
        perror("Receiving Failed\n");
        exit(-1);
    }
    filename[rc] = '\0';

    char contents[500];

    FILE *file = fopen(filename, "r");
    fread(contents, 0, 500, file);
    fclose(file);

    int sd = sendto(sockfd, contents, strlen(contents), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len);
    if(sd<0)
    {
        perror("Sending Failed\n");
        exit(-1);
    }

    printf("Done!!!!!\n");

    return 0;
}
