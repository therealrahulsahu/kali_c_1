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
struct student *input_data()
{
    struct student *temp = (struct student *)malloc(sizeof(struct student));
    printf("Enter Name : ");
    scanf("%s",&(temp->name));
    printf("Enter Roll : ");
    scanf("%d", &(temp->roll));
    printf("Enter 3 Marks : ");
    scanf("%d %d %d", &(temp->m1), &(temp->m2), &(temp->m3));
    return temp;
}
void display_data(struct student *data)
{
    printf("Average : %d\n", data->avg);
    printf("Total : %d\n", data->total);
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

    int n, len;


    struct student *var=input_data();

    sendto(sockfd, (struct student *)var, sizeof(struct student), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));


    n = recvfrom(sockfd, (struct student *)var, sizeof(struct student), MSG_WAITALL, (struct sockaddr *) &servaddr, &len);

    display_data(var);
    close(sockfd);
    return 0;
}
