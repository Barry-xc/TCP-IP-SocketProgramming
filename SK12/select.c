#include<stdio.h>
#include<unistd.h>
#include<sys/time.h>
#include<sys/select.h>
#define BUF_SIZE 30

int main(int argc, char * argv[])
{
	fd_set reads, temps;	// temps为后面提供初始化作用，用于重复初始化reads注册过的监视项。
	int result, str_len;
	char buf[BUF_SIZE];
	struct timeval timeout;

	FD_ZERO(&reads);	// 初始化fd_set变量
	FD_SET(0, &reads);  // 0是标准输入的文件描述符	//将文件描述符0对应的位设置为1。换言之，需要监视标准输入的变化。

	/*
	 timeout.tv_sec = 5;		
	 timeout.tv_usec = 5000;
	*/	//这是为了设置select函数的超时而添加的。但不能在此时设置超时。
		//因为每次调用select函数后，结构体timeval的成员tv_sec和tv_usec的值将被替换为超时前剩余时间。
		//因此，调用select函数前，每次都需要初始化timeval结构体变量。

	while(1)
	{
		temps = reads;	//为了避免上一次循环监测的影响，每次循环的开始都要将fd_set变量的所有位清空，并注册标准输入的文件描述符0，为了记住初始值的设置，必须经过这种复制过程。这是使用select函数的通用方法。
		timeout.tv_sec = 5;		// 将初始化timeval结构体的代码插入循环后，每次调用select函数前都会初始化新值。
		timeout.tv_usec = 0;
		result = select(1, &temps, 0, 0, &timeout); //调用select函数。如果有控制台输入数据，则返回大于0的整数；如果没有输入数据而引发超时，则返回0。
		if(result == -1)
		{
			puts("select() error!");
			break;
		}
		else if(result == 0)
		{
			puts("Time-out!");
		}
		else
		{
			if(FD_ISSET(0, &temps))		//select函数返回大于0的值时运行的区域。验证发生变化的文件描述符是否为标准输入。若是，则从标准输入读取数据并向控制台输出。
			{
				str_len = read(0, buf, BUF_SIZE);
				buf[str_len] = 0;
				printf("message from console: %s", buf);
			}
		}
	}
	return 0;
}
