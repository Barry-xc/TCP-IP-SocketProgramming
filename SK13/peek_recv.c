#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define BUF_SIZE 30
void error_handling(char * message);

int main(int argc, char * argv[])
{
	int acpt_sock, recv_sock;
	struct sockaddr_in acpt_adr, recv_adr;
	int str_len, state;
	socklen_t recv_adr_sz;
	char buf[BUF_SIZE];
	if(argc != 2){
		printf("Usage: %s <port>\n", argv[0]);
		exit(1);
	}

	acpt_sock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&acpt_adr, 0, sizeof(acpt_adr));
	acpt_adr.sin_family = AF_INET;
	acpt_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	acpt_adr.sin_port = htons(atoi(argv[1]));

	if(bind(acpt_sock, (struct sockaddr*)&acpt_adr, sizeof(acpt_adr)) == -1)
		error_handling("bind() error");
	listen(acpt_sock, 5);

	recv_adr_sz = sizeof(recv_adr);
	recv_sock = accept(acpt_sock, (struct sockaddr*)&recv_adr, &recv_adr_sz);

	while(1)
	{
		str_len = recv(recv_sock, buf, sizeof(buf) - 1, MSG_PEEK | MSG_DONTWAIT);//调用recv函数的同时传递MSG_DONTWAIT可选项，这是为了保证即使不存在待读取数据也不会进入阻塞状态。
		if(str_len > 0)
			break;
	}

	buf[str_len] = 0;
	printf("Buffering %d bytes: %s \n", str_len, buf);

	str_len = recv(recv_sock, buf, sizeof(buf) - 1, 0);	// 再次调用recv函数。这次并未设置任何可选项。因此，本次读取的数据将从输入缓冲中删除。
	buf[str_len] = 0;
	printf("Read again: %s \n", buf);
	close(acpt_sock);
	close(recv_sock);
	return 0;
}

void error_handling(char * message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
