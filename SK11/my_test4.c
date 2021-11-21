#include<stdio.h>
#include<unistd.h>
#define BUF_SIZE 30

int main(int argc, char * argv[])
{
	pid_t pid;
	char buf[BUF_SIZE];
	char meg1[] = "I do love C++!";
	char meg2[] = "I will learn hard!";
	int fds1[2], fds2[2];
	pipe(fds1), pipe(fds2);
	int i;

	pid = fork();
	if(pid == 0)
	{
		for(i = 0; i < 3; i++)
		{
			write(fds1[1], meg1, sizeof(meg1));
			read(fds2[0], buf, BUF_SIZE);
			printf("%s\n", buf);
		}
	}
	else
	{
		for(i = 0; i < 3; i++)
		{
			read(fds1[0], buf, BUF_SIZE);
			write(fds2[1], meg2, sizeof(meg2));
			printf("%s\n", buf);
		}
		sleep(1);
	}
	return 0;
}


