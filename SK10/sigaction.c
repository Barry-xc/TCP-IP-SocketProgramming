#include<stdio.h>
#include<unistd.h>
#include<signal.h>

void timeout(int sig)
{
	if(sig == SIGALRM)
		puts("Time out!");
	alarm(2);
}

int main(int argc, char * argv[])
{
	int i;
	struct sigaction act; //为了注册信号处理器，声明sigaction结构体变量并在sa_handler成员中保存函数指针值
	act.sa_handler = timeout;	//在sa_handler成员中保存函数指针值
	sigemptyset(&act.sa_mask); //调用sigemptyset函数将sa_mask成员的所有位初始化为0。
	act.sa_flags = 0;	//sa_flags成员同样初始化为0。
	sigaction(SIGALRM, &act, 0); //注册SIGALRM信号的处理器。

	alarm(2);	//调用alarm函数预约2秒后发生SIGALRM信号。


	for(i = 0; i < 3; i++)
	{
		puts("wait...");
		sleep(100);
	}
	return 0;
}


