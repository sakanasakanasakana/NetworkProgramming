#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE 256

void DieWithError(char *errorMessage){
	perror(errorMessage);
	exit(1);
}

void commun(int sock){
	char buf[BUF_SIZE];
	int len_r;
	char*message = "(」・ω・)」うー！(／・ω・)／にゃー！";
	if(send(sock,message,strlen(message),0)!= strlen(message))
	DieWithError("send() set a message of unexpected bytes");
	if((len_r=recv(sock,buf,BUF_SIZE,0)) <= 0)
	DieWithError("recv()failed");
	buf[len_r] = '\0';
	printf("%s\n",buf);
	return ;
}

int main(int argc, char** argv){
	if (argc !=3)DieWithError("arguments is not available");
	int sock = socket(PF_INET,SOCK_STREAM, 0);
	if(sock < 0) DieWithError("socket()failed");
	char *server_ipaddr = argv[1];// "10.13.64.20"
	int server_port = 10001;
	struct sockaddr_in target;
	target.sin_family = AF_INET;
	target.sin_addr.s_addr = inet_addr(server_ipaddr);
	target.sin_port = htons(server_port);
	if(connect(sock,(struct sockaddr*)&target, sizeof(target))<0)
	DieWithError("connect()failed");
	commun(sock);
	close(sock);
	return 0;
}
