#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#define INT_SIZE 4
#define BUF_SIZE 1024
void error_handling(char * message);

int main(int argc, char * argv[ ])
{
	int serv_sock;
	int clnt_sock;
	int i, str_len, recv_len;
	int length;
	
	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size;

	char recv[BUF_SIZE];
	char message[] = {6,'\0','\0','\0','H','e','l','l','o','?'};
	
	if(argc != 2)
	{
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}
	serv_sock = socket(PF_INET, SOCK_STREAM, 0);	// 调用socket函数创建套接字
	if(serv_sock == -1)
		error_handling("socket() error");
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));
	
	if(bind(serv_sock, (struct sockaddr *) &serv_addr,  sizeof(serv_addr)) == -1)	
		error_handling("bind() error");

	if(listen(serv_sock, 5) == -1)
	{
		error_handling("listen() error");
	}
	clnt_addr_size = sizeof(clnt_addr);
	clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
	if(clnt_sock == -1)
		error_handling("accept() error");
	
	for(i = 0; i < 3; i++)
	{
		length = 0;
		write(clnt_sock, message, sizeof(message));
		read(clnt_sock, &length, INT_SIZE);
		str_len = 0;
		while(str_len < length)
		{
			recv_len = read(clnt_sock, &recv[str_len], BUF_SIZE - 1);
			str_len += recv_len;
		}
		recv[str_len] = 0;
		printf("recieve: %s\n", recv);
	}
	close(clnt_sock);
	close(serv_sock);
	return 0;
}

void error_handling(char * message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
