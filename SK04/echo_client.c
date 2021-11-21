#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#define BUF_SIZE 1024
void error_handling(char * message);

int main(int argc, char * argv[])
{
       	int sock; 
	char message[BUF_SIZE];
       	int str_len;
       	struct sockaddr_in serv_adr;

	if(argc != 3){
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if(sock == -1)
		error_handling("socket() error");

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_adr.sin_port = htons(atoi(argv[2]));

	if(connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)//调用Connect函数。若调用该函数引起的连接请求
																	//被注册到服务器端等待队列，则connect函数将完成
																	//正常调用。因此，即使输出了连接提示字符串"Connect....."
																	//，但如果服务器尚未调用accept函数，也不会真正建立服务关系
		error_handling("connect() error");
	else
		puts("Connected........");

	while(1)
	{
		fputs("Input message(Q to quit):", stdout);
		fgets(message, BUF_SIZE, stdin);

		if(!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
			break;

		write(sock, message, strlen(message));
		str_len = read(sock, message, BUF_SIZE - 1);
		message[str_len] = 0;	//给字符串添加结束符'\0'
		printf("Message from server: %s", message);
	}
	close(sock);	//调用close函数向相应套接字发送EOF（EOF意味着中断连接）
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
