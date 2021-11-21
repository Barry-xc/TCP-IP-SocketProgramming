#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc, char * argv[])
{
	int status;
	pid_t pid = fork();

	if(pid == 0)
	{
		sleep(15);
		return 24;
	}
	else
	{
		while(!waitpid(-1, &status, WNOHANG))	//传递-1，则与wait函数相同，可以等待任意子进程终止。
		{
			sleep(3);
			puts("sleep 3sec.");
		}

		if(WIFEXITED(status))
			printf("Child send %d \n", WEXITSTATUS(status));
	}
	return 0;
}
