#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
void error_handling(char * message);

int main(void)
{
	int fd;
	char buf[] = "Let's go!\n";
	fd = open("data.txt", O_CREAT| O_WRONLY| O_TRUNC);	//文件打开模式为O_CREAT、 O_WRONLY、 O_TRUNC的组合，因此
														//将创建空文件，并只能写。若存在data.txt文件，则清空文件的全部数据。
	if(fd == -1)
		error_handling("open() error!");
	printf("file descriptor: %d \n", fd);
	
	if(write(fd, buf, sizeof(buf)) == -1)	// 相对应于fd中保存的文件描述符的文件传输buf中保存的数据。
		error_handling("write() error!");
	close(fd);
	return 0;
}
void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
