#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#define BUF_SIZE 1024
#define JUMP 4

void error_handling(char * message);
int Calculate(int opercount, int buf[], char oper);

int main(int argc, char * argv[])
{
	int clnt_sock, serv_sock;
	struct sockaddr_in clnt_addr, serv_addr;
	socklen_t clnt_addr_size;
	char message[BUF_SIZE];
	int str_len, recv_len, oper_count;
	int i, result;


	if(argc != 2)
	{
		printf("Usage: %s <port>\n", argv[0]);
	}
	
	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	if(serv_sock == -1)
		error_handling("socket() error!");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));

	if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
		error_handling("bind() error");

	if(listen(serv_sock, 5) == -1)
		error_handling("listen() error");
	
	clnt_addr_size = sizeof(clnt_addr);
	for(i = 0; i < 1; i++)
	{
		oper_count = 0;
		clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
		if(clnt_sock == -1)
			error_handling("accept() error");
		else
			printf("Connected....\n");
		
		read(clnt_sock, &oper_count, 1);
		
		recv_len = 0;
		while(oper_count * JUMP + 1 > recv_len)
		{	
			str_len = read(clnt_sock, &message[recv_len], BUF_SIZE - 1);
			recv_len += str_len;
		}

		result = Calculate(oper_count, (int*)message, message[recv_len - 1]);
		write(clnt_sock, (char *)&result, sizeof(result));

		close(clnt_sock);

	}
	close(serv_sock);
	return 0;
}
int Calculate(int opercount, int buf[], char oper)
{
	int i;
	int result = buf[0];
	switch(oper)
	{
		case '+': 
			for(i = 1; i < opercount; i++)
			{
				result += buf[i];
			}
			break;
			
	}
	return result;
}

void error_handling(char * message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}


