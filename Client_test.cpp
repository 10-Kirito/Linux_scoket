#include"Client_class.h"
#include"Client_class.cpp"
using namespace std;


int main()
{
    //creat the client
    Client client;
    if(!client.Connect("localhost",1234))
    {
        cout << "connect failed!"<<endl;
        return 0;
    }
    //send message to server
    char buff[1024];
    cout << "please input:";
    cin >> buff;
    if(client.sendData(client.getClientfd(),buff,1024))
        cout << "send right"<<endl;
    else
        cout << "send failed"<<endl;

    char recvbuff[1024];
    memset(recvbuff,0,1024);
    if(client.readDta(client.getClientfd(),recvbuff,1024))
        cout << "read right!"<<endl;
    else
        cout << "read failed!"<<endl;


    cout << "------------------Test----------------------"<<endl;

    char test[1024];
    cout << "please input:";
    cin >> test;
    if(write(client.getClientfd(),test,1024) != -1)
        cout << "test right!"<<endl;
    else
        cout << "test failed!"<<endl;
    return 0;
}