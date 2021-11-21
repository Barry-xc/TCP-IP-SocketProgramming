#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
void error_handling(char * message);

int main(int argc, char *argv[])
{
	int sock;
	struct sockaddr_in serv_addr;
	char message[30];
	int str_len = 0;
	int idx = 0, read_len = 0;

	if(argc != 3)
	{
		printf("Usage : %s <IP> <port> \n", argv[0]);
		exit(1);
	}

	sock = socket(PF_INET, SOCK_STREAM, 0);	//创建TCP套接字。若前两个参数传递PF_INET、SOCK_STREAM，则可以省略第三个参数IPPROTO_TCP
	if(sock == -1)
	{
		error_handling("socket() error");
	}

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));

	if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
	{error_handling("connect() error!");}

	while(read_len = read(sock, &message[idx++], 1)) //while循环中反复调用read函数，每次读取一个字节。如果read返回0表示读完，则循环条件为假，跳出while循环
	{
		if(read_len == -1)
			error_handling("read() error!");
		str_len += read_len; // 执行该语句时，变量read_len的值始终为1，因为第37行规定每次仅读取1个字节。str_len中存有读取的总字节数。
	}
	
	printf("Message from server: %s \n", message);
	printf("Function read call count: %d \n", str_len);
	close(sock);
	return 0;
}

void error_handling(char * message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
