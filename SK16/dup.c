#include<stdio.h>
#include<unistd.h>

int main(int argc, char* argv[])
{
	int cfd1, cfd2;
	char str1[] = "C++ \n";
	char str2[] = "I love C++!\n";

	cfd1 = dup(1);	//����dup�����������ļ�������1����׼����1
	cfd2 = dup2(cfd1, 7);//����dup2�����ٴθ������ļ�����������ָ������������ֵΪ7

	printf("fd1 = %d, fd2 = %d \n", cfd1, cfd2);
	write(cfd1, str1, sizeof(str1));//���ø��Ƴ����ļ����������������ͨ����������������֤�Ƿ������ʵ�ʸ��ơ�
	write(cfd2, str2, sizeof(str2));
//��17�С�18����ֹ���Ƴ����ļ���������������1������������˿��Խ��������
	close(cfd1);
	close(cfd2);
	write(1, str1, sizeof(str1));
	close(1);//��ֹ�����ļ�������������޷���ɵ�21�е������
	write(1, str2, sizeof(str2));
	return 0;
}
