#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE 256

void DieWithError(char *errorMessage){
	perror(errorMessage);
	exit(1);
}

void commum (int sock){
	char buf[BUF_SIZE];
	int len_r; 
	if((len_r=recv(sock,buf,BUF_SIZE,0)) <= 0)
	DieWithError("recv()failed");
	while((len_r=recv(sock,buf,BUF_SIZE,0)) > 0){
		buf[len_r] = '\0';
		printf("%s\n",buf);
		
	if(strstr(buf,"\n\n")){
		break;
	}
	}
	if(len_r <= 0){
		DieWithError("send()sent a message of unexpected bytes");
		printf("received HTTP Request.\n");
	printf("HTTP/1.1 200OK \r\n");
	printf("Content-Type:text/html;charset=utf-8\r\n");
	printf("\n");
	printf("<!DOCTYRE html><html><head><title>\n");
	printf("ネットワークプログラミングのWebサイト\n");
	printf("</title></head><body>ネットワークダイスキ</body></html>\n");
	}

	if(send(sock,buf,strlen(buf),0)!=strlen(buf))
	DieWithError("send()sent a message of unexpected bytes");
}

int main(int argc, char **argv){
	int cliSock, servSock = socket(PF_INET,SOCK_STREAM,0);
	struct sockaddr_in servAddress;
	struct sockaddr_in clientAddress;
	socklen_t szClientAddr;
	
	servAddress.sin_family = AF_INET;
	servAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddress.sin_port = htons(80);
	bind(servSock, (struct sockaddr *)&servAddress, sizeof(servAddress));
	listen(servSock,5);
	while(1){
		szClientAddr = sizeof(clientAddress);
		cliSock = accept(servSock, (struct sockaddr *)&clientAddress, &szClientAddr);
		commum(cliSock);
		close(cliSock);
		
	}
	close(servSock);
	return 0;
}