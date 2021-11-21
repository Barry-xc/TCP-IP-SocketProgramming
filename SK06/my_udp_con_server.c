#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#define BUF_SIZE 1024
void error_handling(char * message);

int main(int argc, char * argv[])
{
	int serv_sock;
	struct sockaddr_in serv_addr, clnt_addr;
	socklen_t clnt_addr_size;
	char send[BUF_SIZE];
	char recv[BUF_SIZE];

	if(argc != 2)
	{
		printf("Usage: %s <port>\n", argv[0]);
		exit(1);
	}
	
	serv_sock = socket(PF_INET, SOCK_DGRAM, 0);
	if(serv_sock == -1)
		error_handling("socket() error");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));

	if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1 )
		error_handling("bind() error");

	clnt_addr_size = sizeof(clnt_addr);
	fputs("input q or Q to quit\n", stdout);
	while(1)
	{
		recvfrom(serv_sock, recv, BUF_SIZE - 1, 0, 
				(struct sockaddr*)&clnt_addr, &clnt_addr_size);
		if(!strcmp(send, "q\n") || !strcmp(send, "Q\n")
				|| !strcmp(recv, "q\n") || !strcmp(recv, "Q\n"))// 这一行作用是只要对方关闭套接字，该程序也退出了。
			break;
		printf("recv: %s", recv);//这里面自动换行的原因是，字符串里保存了回车，所以这里就不必要加上\n了

		fputs("send: ", stdout);
		fgets(send, BUF_SIZE, stdin);
		sendto(serv_sock, send, strlen(send), 0,
			       	(struct sockaddr*)&clnt_addr, clnt_addr_size);

		memset(recv, '\0', sizeof(recv));
	}
}

void error_handling(char * message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

