#include"Server_class.h"
#include"Server_class.cpp"
using namespace std;

int main(int argc,char * argv[])
{
    //creat the server
    Server server;
    if(!server.InitServer(argv[1]))
        return 0;

    for(int i = 1;i <= 5;i ++)
    
    {
        if(!server.Accept())
        return 0;
        cout << "Client " << i << "has connectd!"<<endl;
 
    char recvbuff[1024];
    memset(recvbuff,0,1024);
    if(server.readDta(server.getClientfd(),recvbuff,1024))
        cout << recvbuff<<endl;
    else
        cout << "receive failed"<<endl;

    char sendbuff[1024];
    cout << "please reply:";
    cin >> sendbuff;
    if(server.sendData(server.getClientfd(),sendbuff,1024))
        cout << "send right"<<endl;
    else
        cout << "send failed"<<endl;


    char test[1024];
    int count = 0;
    int read_len;
    int str_len = 0;
    while(read_len = read(server.getClientfd(),&test[count ++ ],1))
    {
        if(read_len == -1)
        {
            cout << "read wrong"<<endl;
            return 0;
        }
        str_len += read_len;
    }

    cout <<"read right!"<<endl;
    cout <<"Message from client:"<< test <<endl;
    cout << "Function read call count:"<<str_len<<endl;
    close(server.getClientfd());
    }

    return 0;
}