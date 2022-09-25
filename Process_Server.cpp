#include"Server_class.h"
#include"Server_class.cpp"

using namespace std;


int main(int argc,char *argv[])
{
    //creat the server
    Server server;
    pid_t pid;//the number of the son

    if(argc != 2)
    {
        printf("Usage : %s <port>\n",argv[0]);
        exit(1);
    }

    if(!server.InitServer(argv[1]))
        return 0;
    while(1)
    {
        if(!server.Accept())
            continue;
        else
            printf("The client %s has connectted!\n",server.getClientIP());

        //create the son
        pid = fork();
        if(pid == -1)//creat the son failed
        {
            server.closeClientFd();
            continue;
        }
        else if(!pid)//creat the son right,this is the son
        {
            cout << "process son creat"<<endl;
            server.closeServerFd();

            char sendbuff[1024];
            char recvbuff[1024];
            memset(recvbuff,0,1024);

            bool out;
            pid_t talk;
            talk = fork();//creat the grandson to recv and send
            if(talk == -1)
            {
                cout << "creat the grandson failed"<<endl;
            }
            if(!talk)//this is the grandson,used to recv
            {
                //server.closeClientFd();
                while(1)
                {
                    if((out = server.readDta(server.getClientfd(),recvbuff,1024)))
                        cout << "message from client:"<<recvbuff<<endl;
                    out = false;
                    //sleep(2);
                }
            }
            else//this is the son,used to send
            {
                while(1)
                {
                    cout << "Server please input:"<<endl;
                    cin >> sendbuff;
                    server.sendData(server.getClientfd(),sendbuff,strlen(sendbuff));
                    //cout << "send right"<<endl;
                    //sleep(2);
                }
            }
        }
        else//this is the father
        {
            server.closeClientFd();
        }
    }
    

    return 0;
}
