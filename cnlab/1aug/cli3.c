#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT  9000

int input_data(int var[], int n)
{
    printf("Enter Elements :\n");
    for (int i=0; i < n; ++i) {
        scanf("%d", &var[i]);
    }
}
void display_data(int data[], int n)
{
    printf("Sorted Array : ");
    for (int i = 0; i<n; ++i) {
        printf("%d ", data[i]);
    }
    printf("\n");
}
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

    int size, len;

    int n;
    printf("Enter No. of elements : ");
    scanf("%d", &n);
    int var[100];
    input_data(var, n);


    sendto(sockfd, (const int *)var, n* sizeof(int), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));

    size = recvfrom(sockfd, (int *)var, 1000, MSG_WAITALL, (struct sockaddr *) &servaddr, &len);

    display_data(var, size/ sizeof(int));
    return 0;
}
