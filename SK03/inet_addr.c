#include<stdio.h>
#include<arpa/inet.h>

int main(int argc, char * args[])
{
	char *addr1 = "1.2.3.4";
	char *addr2 = "1.2.3.256";	// 1���ֽ��ܱ�ʾ���������Ϊ255��Ҳ����˵�����Ǵ����IP��ַ�����øô����ַ��֤inet_addr��ɣũ���Ĵ�����������

	unsigned long conv_addr = inet_addr(addr1);	//��������
	if(conv_addr == INADDR_NONE)
		printf("Error occured!\n");
	else
		printf("Network ordered integer addr: %#lx \n", conv_addr);

	conv_addr = inet_addr(addr2);	// ���ó����쳣��
	if(conv_addr == INADDR_NONE)
		printf("Error occureded \n");
	else
		printf("Network ordered integer addr: %#lx \n\n", conv_addr);
	return 0;
}
