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
	int sock;
	struct sockaddr_in serv_addr, clnt_addr;
	socklen_t clnt_addr_size;
	char send[BUF_SIZE];
	char recv[BUF_SIZE];

	if(argc != 2)
	{
		printf("Usage: %s <port>\n", argv[0]);
		exit(1);
	}
	
	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	if(serv_sock == -1)
		error_handling("socket() error");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));

	if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1 )
		error_handling("bind() error");
	
	if(listen(serv_sock, 5) == -1)
		error_handling("listen() error");
	
	clnt_addr_size = sizeof(clnt_addr);

	clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
	fputs("input q or Q to quit\n", stdout);
	while(1)
	{
		read(clnt_sock, recv, BUF_SIZE - 1);
		if(!strcmp(send, "q\n") || !strcmp(send, "Q\n")
				|| !strcmp(recv, "q\n") || !strcmp(recv, "Q\n"))// ��һ��������ֻҪ�Է��ر��׽��֣��ó���Ҳ�˳��ˡ�
			break;
		printf("recv: %s", recv);//�������Զ����е�ԭ���ǣ��ַ����ﱣ���˻س�����������Ͳ���Ҫ����\n��

		fputs("send: ", stdout);
		fgets(send, BUF_SIZE, stdin);
		write(clnt_sock, send, BUF_SIZE - 1);
		memset(recv, '\0', sizeof(recv));
	}
}

void error_handling(char * message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

