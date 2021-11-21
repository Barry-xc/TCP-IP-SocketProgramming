#include<stdio.h>
#include<fcntl.h>

int main(void)
{
	FILE* fp;
	int fd = open("data.dat", O_WRONLY| O_CREAT| O_TRUNC);
	if(fd == -1)
	{
		fputs("file open error", stdout);
		return -1;
	}

	fp = fdopen(fd, "w");	//调用fopen函数将文件描述符转化为FILE指针。此时向第二个参数传递了"w",因此返回写模式的FIlE指针。
	fputs("Network C programming \n", fp);
	fclose(fp);	// 调用fclose函数，利用FIEL指针关闭文件。
	return 0;
}
