#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUF_SIZE 1024
#define RLT_SIZE 4 //�������ݵĵ��ֽڴ�С��������ʾ����������Ĵ�С��
#define OPSZ 4      // ͬ��
void error_handling(char *message);

int main(int argc, char *argv[])
{
    int sock;
    char opmsg[BUF_SIZE];
    int result, opnd_cnt, i;
    struct sockaddr_in serv_adr;
    if (argc != 3)
    {
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1)
        error_handling("socket() error");

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_adr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("connect() error!");
    else
        puts("Connected...........");

    fputs("Operand count: ", stdout);
    scanf("%d", &opnd_cnt);     //�������������
    opmsg[0] = (char)opnd_cnt;  //���������������ǿ��ת����char������������opmsg����ΪЭ��涨�������������Ӧͨ��1�ֽ������ʹ��ݣ���˲��ܳ���1�ֽ��������ܹ���ʾ�ķ�Χ��0~255 �� -128~127������Ϊ���������Ǹ���������ʹ���޷��������͸�������ΧӦ��Ϊ 0~255��

    for (i = 0; i < opnd_cnt; i++)
    {
        printf("Operand %d: ", i + 1);
        scanf("%d", (int *)&opmsg[i * OPSZ + 1]); // �������Ͳ����������浽����opmsg��4�ֽ�int��Ҫ���浽char���飬�������ǰ�ַ������һ���ֽڿռ�ת����4���ֽڿռ䣬����Ҳ���ǽ�char*ת����int*��
    }
    fgetc(stdin);   //����fgetcɾ���������е��ַ�\n
    fputs("Operator: ", stdout);
    scanf("%c", &opmsg[opnd_cnt * OPSZ + 1]); //���������
    write(sock, opmsg, opnd_cnt * OPSZ + 2); //����һ��write�������д��䣬Ҳ���Էֳɶ�Ρ�������ΪTCP�в��������ݱ߽硣
    read(sock, &result, RLT_SIZE);   //����������˴�����������������յ����ݳ���Ϊ4�ֽڣ�����1��read�������ɽ�����ϡ�

    printf("Operation result: %d \n", result);
    close(sock);
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
