#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>

char val;

void handler(int sig)
{
	if(sig == SIGINT)
	{
		printf("quit y/n?\n");
	}
	scanf("%c", &val);
}


int main(int argc, char * argv[])
{
	signal(SIGINT, handler);
	while(1)
	{
		printf("I do love C++!\n");
		sleep(1);
		if(val == 'y')
			break;
	}
	return 0;
}
