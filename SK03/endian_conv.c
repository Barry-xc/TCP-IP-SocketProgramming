#include<stdio.h>
#include<arpa/inet.h>

int main(int argc, char * argv[])
{
	unsigned short host_port = 0x1234;
	unsigned short net_port;
	unsigned long host_addr=0x12345678;
	unsigned long net_addr;
���ı�֮����ֽ��򱣴档

// ��12��13�У�����host_port��host_addr�е�����ת��Ϊ�����ֽ��������л���ΪС����CPU����	net_port = htons(host_port);
	net_addr = htonl(host_addr);

	printf("Host ordered port: %#x \n", host_port);
	printf("Network order port: %#x \n", net_port);
	printf("Host order address: %#lx \n", host_addr);
	printf("Network order address %#lx \n", net_addr);
	return 0;
}
