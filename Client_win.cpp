#include<iostream>
#include<winsock.h>
#pragma comment(lib,"ws2_32.lib")//�����׽��ֿ�
using namespace std;
//��ʼ���׽��ֿ�
void Initialization()
{
	WORD w_req = MAKEWORD(2, 2);
	WSADATA wsadata;
	int err;
	err = WSAStartup(w_req, &wsadata);
	if (!err)
	{
		cout << "��ʼ���׽��ֿ�ɹ���" << endl;
	}
	else
	{
		cout << "��ʼ���׽��ֿ�ʧ�ܣ�" << endl;
	}
	//
	//���汾��
	if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2) {
		cout << "�׽��ֿ�汾�Ų�����" << endl;
	}
	else {
		cout << "�׽��ֿ�汾��ȷ��" << endl;
	}
}

int main()
{
	Initialization();

	//����˵�ַ
	SOCKADDR_IN server_addr;
	server_addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(12341);

	//�����׽��֣���������connection�������ӳɹ�֮�󷵻ص��׽���
	SOCKET server = socket(AF_INET,SOCK_STREAM,0);

	//��ʼ�������Ӳ���
	if (connect(server, (SOCKADDR*)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		cout << "����������ʧ�ܣ�" << endl;
		WSACleanup();
	}
	else {
		cout << "���������ӳɹ���" << endl;
	}

	char sendchar[1024];
	char recvchar[1024];
	memset(sendchar, 0, 1024);
	//memset(recvchar, 0, 1024);
	int send_len = 0;
	int recv_len = 0;
	//��ʼ��������
	while (1)
	{
		cout << "��������Ϣ��" << endl;
		cin >> sendchar;
		send_len = send(server, sendchar, strlen(sendchar), 0);
		if (send_len < 0)
		{
			cout << "����ʧ��!" << endl;
			break;
		}
		recv_len = recv(server, recvchar, strlen(recvchar), 0);
		if (recv_len < 0)
		{
			cout << "������Ϣʧ��!" << endl;
			break;

		}
		else
		{
			recvchar[recv_len] = '\0';
			cout << "���Է���������Ϣ��"<<recvchar << endl;
			cout << recvchar[0] << endl;
			//printf("���Է���������Ϣ��%s\n", recvchar);
		}

	}
	//�ر��׽���
	closesocket(server);

	//�ͷ�DLL��Դ
	WSACleanup();

	return 0;
}