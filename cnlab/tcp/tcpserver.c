# include<stdio.h>
# include<stdlib.h>
# include<sys/types.h>
# include<sys/socket.h>
# include<unistd.h>
# include<arpa/inet.h>
# include<netinet/in.h>
# include<string.h>

int main(int argc,char *argv[]){
	int sockfd,cli_size,newsockfd,portno;
	long int len;
	struct sockaddr_in serv_addr,cli_addr;
	
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(atoi(argv[1]));
	serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	if((sockfd=socket(AF_INET,SOCK_STREAM,0)) < 0){
		perror("Socket failed");
		exit(1);
	}
	
	if(bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0){
		perror("Bind failed");
		exit(1);
	}
	
	if(listen(sockfd,5) < 0){
		perror("listen failed");
		exit(1);
	}
	socklen_t addr_size;
	char buff[100];
	int i=0;
	for( ; ; )
	{
	if((newsockfd=accept(sockfd,(struct sockaddr *)&cli_addr,&addr_size)) < 0)
	{
		perror("New socket for data transmission failed");
		printf("%d",newsockfd);
		exit(1);
	}
	i++;
	printf("No. of connections:%d\n",i);
	while(1)
	{
		bzero(buff,'0');
		len=recv(newsockfd,buff,sizeof(buff),0);
		buff[len]='\0';
		send(newsockfd,buff,strlen(buff),0);
			if(strcmp(buff,"exit") == 0)
			break;
		printf("Aaaya :%ld",len);
		}
	}	
}
