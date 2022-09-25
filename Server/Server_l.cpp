#include<iostream>
#include<winsock.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
void Initialization()
{
	WORD w_req = MAKEWORD(2,2);
	WSADATA wsadata;
	int err;
	err = WSAStartup(w_req, &wsadata);
	if (!err)
	{
		cout << "Initialization!" << endl;
	}
	else
	{
		cout << "Not Initialization!" << endl;
	}
	if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2) {
		cout << "The Version is wrong!" << endl;
	}
	else {
		cout << "The Version is right!" << endl;
	}

}

int main()
{
	Initialization();
	//STEP 1:
	//make scoket()
	
	SOCKET s_server = socket(AF_INET, SOCK_STREAM, 0);

	/*the addr of the server socket
	struct sockaddr_in
	{
		short sin_family;
		unsigned short sin_port;
		struct sin_addr;
		char sin_zero[8];
	};
	
	*/
	//the addr of the server socket
	SOCKADDR_IN server_addr;
	
	//the detail of the addr
	server_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(12341);


	//STEP 2
	//binding...
	/*
	bind{
		SCOKET s;
		const struct sockaddr *myaddr,
		int numelen
	}
	
	*/
	if (bind(s_server, (SOCKADDR*)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{//
		cout << "Bind wrong!£¡" << endl;
		WSACleanup();
	}
	else
	{
		cout << "Bind successfully!" << endl;
	}

	if (listen(s_server, SOMAXCONN) < 0) {
		cout << "Listen wrong!" << endl;
		WSACleanup();
	}
	else
		cout << "Listen right!" << endl;

	cout << "acceptting....." << endl;

	
	int len = sizeof(SOCKADDR);

	SOCKADDR_IN client_addr;

	//the client socket

	SOCKET s_accept = accept(s_server,(SOCKADDR * )&client_addr,&len);

	if (s_accept == SOCKET_ERROR)
	{
		cout << "Connect wrong!" << endl;
		WSACleanup();
		return 0;
	}

	cout << "Connect successfully!" << endl;

	int recv_len = 0;
	int send_len = 0;
	char recvdata[1024];
	char senddata[1024];
	//memset(recvdata, 0, 1024);
	memset(senddata, 0, 1024);

	while (1)
	{
		recv_len = recv(s_accept, recvdata, strlen(recvdata), 0);
		
		recvdata[recv_len] = '\0';
		if (recv_len < 0)
		{
			cout << "Wrong" << endl;
			break;
		}
		else
		{
			cout << "From the Client:" << recvdata << endl;
			
		}

		
		cin >> senddata;
		send_len = send(s_accept, senddata, strlen(senddata), 0);
		if (send_len < 0)
		{
			cout << "Send wrong!" << endl;
			break;
		}


	}



	
	return 0;

}