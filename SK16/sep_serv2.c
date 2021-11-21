#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#define BUF_SIZE 1024

void error_handling(char* message);

int main(int argc, char* argv[])
{
	int serv_sock, clnt_sock;
	struct sockaddr_in serv_addr, clnt_addr;
	socklen_t clnt_addr_size;
	char buf[BUF_SIZE] = {0,};
	FILE* readfp;
	FILE* writefp;

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	if(serv_sock == -1)
		error_handling("socket() error");

	if(argc != 2)
	{
		printf("Usage: %s <port>\n", argv[0]);
		exit(1);
	}

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));

	if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
		error_handling("bind() error");

	if(listen(serv_sock, 5) == -1)
		error_handling("listen() error");
	clnt_addr_size = sizeof(clnt_addr);
	clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
	if(clnt_sock == -1)
		error_handling("accept() error");
	
	readfp = fdopen(clnt_sock, "r");
	writefp = fdopen(dup(clnt_sock), "w");//通过dup函数的返回值生成FILE指针

	fputs("FROM SERVER: Hi~ client? \n", writefp);
	fputs("I love C++\n", writefp);
	fputs("learn hard!\n", writefp);
	fflush(writefp);

	shutdown(fileno(writefp), SHUT_WR);	//通过fileno函数生成FILE指针。
	fclose(writefp);

	fgets(buf, sizeof(buf), readfp);
	fputs(buf, stdout);
	fclose(readfp);
	return 0;
}
void error_handling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
