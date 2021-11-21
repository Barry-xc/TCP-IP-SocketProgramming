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
	int sock;
	struct sockaddr_in serv_addr;
	char send[BUF_SIZE];
	char recv[BUF_SIZE];
	int str_len;
	int match;
	char * filename;
	FILE * fd;

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if(sock == -1)
		error_handling("socket() error");

	if(argc != 3)
	{
		printf("Usage: %s <IP> <port>\n", argv[0]);
		exit(1);
	}

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));

	if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
		error_handling("connected() error");
	else
		printf("Connected...\n");

	printf("INPUT q/Q TO QUIT!\n");

	match = 0;

	while(1)
	{
		memset(send, 0, sizeof(send));
		printf("download filename:");
		scanf("%s", send + 1);
		fgetc(stdin);
		filename = send + 1; // filename is const char*, suit for fopen()
		if(!strcmp(filename, "q") || !strcmp(filename, "Q"))
		{
			close(sock);
			return 0;
		}
		send[0] = (char)strlen(filename);
		
		write(sock, send, strlen(send));
		read(sock, &match, 1);
		if(match == 1)
			break;
		else 
			printf("no this file!\n");

	}

	if(match == 1)
	{
		fd = fopen(filename, "wb");
		while((str_len = read(sock, recv, BUF_SIZE)) != 0)
			fwrite((void*)recv, 1, str_len, fd);

		printf("Download Sucessful!\n");
		fclose(fd);
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
