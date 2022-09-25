#include"Client_class.h"
#include"Client_class.cpp"
using namespace std;

int main(int argc,char *argv[])
{
    //creat the client
    Client client;
    if(!client.Connect(argv[1],atoi(argv[2])))
    {
        cout << "connect failed!"<<endl;
        return 0;
    }
    //send the name to server
    string name;
    cout << "please input your name: ";
    cin >> name;
    write(client.getClientfd(),(const char *)name.c_str(),name.length());
    string name_0;
    cout << "please input who you want to talk:";
    cin >> name_0;
    write(client.getClientfd(),(const char *)name.c_str(),name.length());
   //send message to server and read message from server
    char buff[1024];
    char recvbuff[1024];
    memset(recvbuff,0,1024);
    bool out;
    pid_t pid = fork();
    if(pid == -1)
    {
        cout << "process creat failed"<<endl;
        return 0;
    }
    if(pid != 0)//this is the father,used to send
    {
        while(1)
        {
            cout << "please input:"<<endl;
            cin >> buff;
            client.sendData(client.getClientfd(),buff,1024);
            //cout << "\nsend right"<<endl;
            //sleep(2);
        }
    }
    else//this is the son,used to recv
    {
        while(1)
        {
            if(out = client.readDta(client.getClientfd(),recvbuff,1024))
                cout << "message from server:"<<recvbuff<<endl;
            out  = false;
            //sleep(2);
        }
    }

    return 0;
}