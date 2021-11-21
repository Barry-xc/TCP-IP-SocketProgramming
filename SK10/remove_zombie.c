#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>

void read_childproc(int sig)
{
	int status;
	pid_t id = waitpid(-1, &status, WNOHANG);
	if(WIFEXITED(status))
	{
		printf("Removed proc id: %d \n", id);
		printf("Child send: %d \n", WEXITSTATUS(status));
	}
}

int main(int argc, char * argv[])
{
	pid_t pid;
	struct sigaction act;
	act.sa_handler = read_childproc; //为了注册信号处理器，声明sigaction结构体变量并在sa_handler成员存函数指针值。
	sigemptyset(&act.sa_mask); // 调用sigemtpyset函数将sa_mask成员的所有位初始化为0.
	act.sa_flags = 0;	//sa_flags成员同样初始化为0。
	sigaction(SIGCHLD, &act, 0);	//注册SIGCHILD信号对应的处理器。若子进程终止，则调用第七行定义的函数，处理函数中调用了waitpid函数，所以子进程将正常终止，不会成为僵尸进程。

	pid = fork();
	if(pid == 0)
	{
		puts("Hi! I'm child process");
		sleep(10);
		return 12;
	}
	else
	{
		printf("Child proc id: %d \n", pid);
		pid = fork();
		if(pid == 0)
		{
			puts("Hi! I'm child process");
			sleep(10);
			exit(24);
		}
		else
		{
			int i;
			printf("Child proc id: %d \n", pid);
			for(i = 0; i < 5; i++)	//为了等待发生SIGCHLD信号，是父进程共暂停5次，每次间隔5秒。发生信号时，父进程将被唤醒，因此实际暂停时间不到25秒。
			{
				puts("wait...");
				sleep(5);
			}
		}
	}
	return 0;
}
