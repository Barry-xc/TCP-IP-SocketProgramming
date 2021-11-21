#include<stdio.h>
#include<unistd.h>
#include<signal.h>

void timeout(int sig)	//定义信号处理函数，这种类型的函数称为信号处理器（Handler）
{
	if(sig == SIGALRM)
		puts("Time out!");
	alarm(2);
}

void keycontrol(int sig)	//定义信号处理函数，这种类型的函数称为信号处理器（Handler）
{
	if(sig == SIGINT)
		puts("CTRL+C pressed");
}

int main(int argc, char * argv[])
{
	int i;
	signal(SIGALRM, timeout);	//注册SIGALRM信号及其处理器
	signal(SIGINT, keycontrol); //注册SIGINT信号，及其处理器
	alarm(2);	//预约2秒后发生SIGALRM信号。

	for(i = 0; i < 3; i++)
	{
		puts("wait...");
		sleep(100); 
	}
	return 0;

}

