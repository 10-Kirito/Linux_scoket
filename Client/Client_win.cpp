#include<iostream>
#include<winsock.h>
#pragma comment(lib,"ws2_32.lib")//加载套接字库
using namespace std;
//初始化套接字库
void Initialization()
{
	WORD w_req = MAKEWORD(2, 2);
	WSADATA wsadata;
	int err;
	err = WSAStartup(w_req, &wsadata);
	if (!err)
	{
		cout << "初始化套接字库成功！" << endl;
	}
	else
	{
		cout << "初始化套接字库失败！" << endl;
	}
	//
	//检测版本号
	if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2) {
		cout << "套接字库版本号不符！" << endl;
	}
	else {
		cout << "套接字库版本正确！" << endl;
	}
}

int main()
{
	Initialization();

	//服务端地址
	SOCKADDR_IN server_addr;
	server_addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(12341);

	//创建套接字，用来接收connection函数连接成功之后返回的套接字
	SOCKET server = socket(AF_INET,SOCK_STREAM,0);

	//开始进行连接操作
	if (connect(server, (SOCKADDR*)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		cout << "服务器连接失败！" << endl;
		WSACleanup();
	}
	else {
		cout << "服务器连接成功！" << endl;
	}

	char sendchar[1024];
	char recvchar[1024];
	memset(sendchar, 0, 1024);
	//memset(recvchar, 0, 1024);
	int send_len = 0;
	int recv_len = 0;
	//开始发送数据
	while (1)
	{
		cout << "请输入信息：" << endl;
		cin >> sendchar;
		send_len = send(server, sendchar, strlen(sendchar), 0);
		if (send_len < 0)
		{
			cout << "发送失败!" << endl;
			break;
		}
		recv_len = recv(server, recvchar, strlen(recvchar), 0);
		if (recv_len < 0)
		{
			cout << "接收信息失败!" << endl;
			break;

		}
		else
		{
			recvchar[recv_len] = '\0';
			cout << "来自服务器的信息："<<recvchar << endl;
			cout << recvchar[0] << endl;
			//printf("来自服务器的信息：%s\n", recvchar);
		}

	}
	//关闭套接字
	closesocket(server);

	//释放DLL资源
	WSACleanup();

	return 0;
}