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

	fp = fdopen(fd, "w");	//����fopen�������ļ�������ת��ΪFILEָ�롣��ʱ��ڶ�������������"w",��˷���дģʽ��FIlEָ�롣
	fputs("Network C programming \n", fp);
	fclose(fp);	// ����fclose����������FIELָ��ر��ļ���
	return 0;
}
