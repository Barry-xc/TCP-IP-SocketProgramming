#include<stdio.h>
#include<unistd.h>
#define BUF_SIZE 30

int main(int argc, char * argv[])
{
	int fds[2];
	char str[] = "Who are you?";
	char buf[BUF_SIZE];
	pid_t pid;

	pipe(fds);	//调用pipe函数创建管道，fds数组中保存用于I/O的文件描述符
	pid = fork();	//调用fork函数。子进程将拥有通过pipe函数调用获取的2个文件描述符。注意！复制的并非管道，而是用于管道I/O的文件描述符。至此，父子进程同时拥有I/O文件描述符。
	if(pid == 0)
	{
		write(fds[1], str, sizeof(str));	//子进程向管道入口传递字符串
	}
	else
	{
		read(fds[0], buf, BUF_SIZE);	// 父进程从管道出口接收字符串
		puts(buf);
	}
	return 0;
}
