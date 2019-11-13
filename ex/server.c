#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
int main()
{
    int soc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}
