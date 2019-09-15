# include<stdio.h>
# include<stdlib.h>
# include<sys/types.h>
# include<sys/socket.h>
# include<unistd.h>
# include<arpa/inet.h>
# include<netinet/in.h>
# include<string.h>

int main(int argc,char *argv[]){
	int sockfd,len;
	struct sockaddr_in serv_addr;
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(atoi(argv[1]));
	serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	if((sockfd=socket(AF_INET,SOCK_STREAM,0)) < 0){
		perror("Socket failed");
		exit(1);
	}
	
	if(connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0){
	perror("connection failed");
	exit(1);
	}
	char str[100];
	char buff[100];
	for( ; ;){
		scanf("%s",str);
		bzero(buff,'0');
		send(sockfd,str,sizeof(str),0);
		len=recv(sockfd,buff,sizeof(buff),0);
		buff[len]='\0';
		if(strcmp(buff,"exit") == 0)
			break;
		fputs(buff,stdout);
	}
	close(sockfd);
}
