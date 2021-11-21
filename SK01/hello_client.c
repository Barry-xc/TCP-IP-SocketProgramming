#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
void error_handling(char *message);

int main(int argc, char * argv[])
{
	int sock;
	struct sockaddr_in serv_addr;
	char message[30];
	int str_len;
	
	if(argc != 3)
	{
		printf("usage: %s <IP> <port>\n", argv[0]);
		exit(1);
	}
	
	sock = socket(PF_INET, SOCK_STREAM, 0);		// 创建套接字，此时套接字还不能够分为服务器端和客户端。如果紧接着
												// 调用bind、listen函数，将成为服务器端套接字；如果调用connect函数
												//，将成为客户端套接字。
	if(sock == -1)
		error_handling("socket() error");
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));
	
	if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)	// 调用connect函数向服务器端发送连接请求
		error_handling("connect() error!");
	
	str_len=read(sock, message, sizeof(message) - 1);
	if(str_len == -1)
	{
		error_handling("read() error!");
	}
	
	printf("Message from server : %s\n", message);
	close(sock);
	return 0;
}

void error_handling(char * message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
