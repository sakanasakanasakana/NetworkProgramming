#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE 256
//http://localhost/
void DieWithError(char *errorMessage){
	perror(errorMessage);
	exit(1);
}
void commum (int sock){
	char buf[BUF_SIZE];
	char buf_old[BUF_SIZE];
	char buf2[2*BUF_SIZE];
	int len_r; 
	char response[BUF_SIZE];
	
	buf_old[0] = '\0';
	while((len_r=recv(sock,buf,BUF_SIZE,0)) > 0){
		buf[len_r] = '\0';
		sprintf(buf2,"%s%s",buf_old,buf);
		
	if(strstr(buf,"\r\n\r\n")){
		break;
	}
	}
		sprintf(buf_old, "%s",buf);
	
	if (len_r <= 0)
		DieWithError("received() failed.");
    
    printf("received HTTP Request.\n");

    sprintf(response, "HTTP/1.1 200 OK\r\n");
    if(send(sock, response, strlen(response), 0) != strlen(response))
        DieWithError("send() sent a message of unexpected bytes");
    
    sprintf(response, "Content-Type: text/html; charset=utf-8\r\n");
    if(send(sock, response, strlen(response), 0) != strlen(response))
        DieWithError("send() sent a message of unexpected bytes");
        
    sprintf(response, "\r\n");
    if(send(sock, response, strlen(response), 0) != strlen(response))
        DieWithError("send() sent a message of unexpected bytes");
    
    sprintf(response, "<!DOCTYPE html><html><head><title>");
    if(send(sock, response, strlen(response), 0) != strlen(response))
        DieWithError("send() sent a message of unexpected bytes");
    
    sprintf(response, "ネットワークプログラミングのwebサイト");
    if(send(sock, response, strlen(response), 0) != strlen(response))
        DieWithError("send() sent a message of unexpected bytes");
    
    sprintf(response, "</title></head><body>ネットワークダイスキ</body></html>");
		if(send(sock, response, strlen(response), 0) != strlen(response))
        DieWithError("send() sent a message of unexpected bytes");


	if(send(sock,buf,strlen(buf),0)!=strlen(buf))
	DieWithError("send()sent a message of unexpected bytes");
}

int main(int argc, char **argv){
	struct sockaddr_in clientAddress;
	unsigned int szClientAddr;
	int cliSock;

	int servSock = socket(PF_INET, SOCK_STREAM, 0);
    if (servSock < 0)
        DieWithError("socket() failed");
    
    struct sockaddr_in servAddress;
	
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