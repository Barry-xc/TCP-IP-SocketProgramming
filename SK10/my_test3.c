#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<stdlib.h>

int main(int argc, char * argv[])
{
	int sock;
	sock = socket(PF_INET, SOCK_DGRAM, 0);
	pid_t pid;
	pid = fork();
	if(pid == 0)
	{
		printf("child's sock's val: %d \n", sock);
		exit(1);
	}
	else
	{
		printf("parent's sock's val: %d \n", sock);
	}
	return 0;
}
