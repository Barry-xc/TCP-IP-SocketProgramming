#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#define BUF_SIZE 1024
void error_handling(char *message);

int main(int argc, char * argv[])
{
	int sock;
	struct sockaddr_in serv_addr;
	socklen_t sock_addr_size;
	char send[BUF_SIZE];
	char recv[BUF_SIZE];

	if(argc != 3)
	{
		printf("Usage: %s <IP> <port>\n", argv[0]);
		exit(1);
	}

	sock = socket(PF_INET, SOCK_DGRAM, 0);
	if(sock == -1)
		error_handling("socket() error");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));

	if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)//if语句在这里没意义，因为并这里不是为了进行连接操作，而是注册服务器端的网络地址信息。
		error_handling("connect() error");
	
	fputs("input q or Q to quit\n", stdout);
	while(1)
	{
		fputs("send: ", stdout);
		fgets(send, BUF_SIZE, stdin);
		write(sock, send, strlen(send));
		if(!strcmp(send, "q\n") || !strcmp(send, "Q\n")
				|| !strcmp(recv, "q\n") || !strcmp(recv, "Q\n")) // 这一行作用是只要对方关闭套接字，该程序也退出了。
			break;
		read(sock, recv, BUF_SIZE - 1);
		printf("recv: %s", recv);//这里面自动换行的原因是，字符串里保存了回车，所以这里就不必要加上\n了
		memset(recv, '\0' , sizeof(recv));

	}
	close(sock);
	return 0;
}

void error_handling(char * message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

