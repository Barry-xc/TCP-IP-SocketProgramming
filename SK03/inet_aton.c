#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
void error_handling(char * message);

int main(int argc, char *argv[])
{
	char * addr = "127.232.124.79";
	struct sockaddr_in addr_inet;

	if(!inet_aton(addr, &addr_inet.sin_addr))//ת�����IP��ַ��Ϣ�鹹���浽sockaddr_in��in_addr�ͱ����������塣���inet_aton�����ĵڶ�������Ҫ��õ�in_addr�͵ı�����ֵַ�����ʡȥ���ֶ�����IP��ַ��Ϣ�Ĺ��̡�
		error_handling("Conversion error");
	else
		printf("Network order integer addr: %#x \n",
				addr_inet.sin_addr.s_addr);
	return 0;
}

void error_handling(char * message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
