#include<stdio.h>
#include<unistd.h>
#define BUF_SIZE 30

int main(int argc, char * argv[])
{
	int fds[2];
	char str1[] = "Who are you?";
	char str2[] = "Thank you for you message";
	char buf[BUF_SIZE];
	pid_t pid;

	pipe(fds);
	pid = fork();
	if(pid == 0)
	{
		write(fds[1], str1, sizeof(str1));	
		sleep(2);	// 当注释掉后，子进程将会再下一行的read读取自己写入管道的数据，管道中的数据被取出，从而父进程调用read函数时因为没有数据读取而堵塞。
		read(fds[0], buf, BUF_SIZE);
		printf("Child proc output: %s \n", buf);
	}
	else
	{
		sleep(1);
		read(fds[0], buf, BUF_SIZE);
		printf("Parent proc output: %s \n", buf);
		write(fds[1], str2, sizeof(str2));
		sleep(3);	// 在子进程结束前弹出控制提示符
	}
	return 0;
}
