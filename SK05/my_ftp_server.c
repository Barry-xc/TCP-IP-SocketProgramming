#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#define BUF_SIZE 30
void error_handling(char * message);

int main(int argc, char * argv[])
{
	int clnt_sock, serv_sock;
	struct sockaddr_in clnt_addr, serv_addr;
	socklen_t clnt_addr_size;
	char send[BUF_SIZE];
	char recv[BUF_SIZE];
	int str_len, recv_len;
	int match;
	FILE * fd;
	int i;

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
	else
		printf("Connected...\n");

	while(1)
	{
		memset(recv, 0, sizeof(recv));
		str_len = 0;
		read(clnt_sock, &str_len, 1);
		printf("filename.len: %d\n", str_len);
		read(clnt_sock, recv, str_len);	//recevie filename;
		if((fd = fopen(recv, "rb")) != NULL)
		{
			match = 1;
			write(clnt_sock, &match, 1);
			while(1)
			{
				recv_len = fread((void*)send, 1, BUF_SIZE, fd);
				if(recv_len < BUF_SIZE)
				{
					write(clnt_sock, send, recv_len);
					break;
				}
				write(clnt_sock, send, BUF_SIZE);
			}
			shutdown(clnt_sock, SHUT_WR);
			fclose(fd);
			printf("Transfer Succesful!\n");
			break;
		}
		else
		{
			match = 0;
			write(clnt_sock, &match, 1);
		}

	}
	close(clnt_sock);
	close(serv_sock);
}
void error_handling(char * message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

