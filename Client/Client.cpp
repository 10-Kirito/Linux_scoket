#include<sys/socket.h>
#include<sys/types.h>
#include<sys/errno.h>
#include<arpa/inet.h>
#include<netdb.h>

#include<string.h>
#include<iostream>
#include<unistd.h>
#include<stdlib.h>
using namespace std;
int main()
{
    //creat client socket
    int client = socket(AF_INET,SOCK_STREAM,0);
    if(client == -1)
    {
         perror("socket creat failed:"); 
         return -1;
    }


    //addr of the client
    struct sockaddr_in client_addr;
    memset(&client_addr,0,sizeof(client_addr));
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(atoi("2222"));
    //advanced put addr
    struct hostent * h;
    if((h = gethostbyname("192.168.222.129")) == 0)
    {
        printf("gethost failed!\n");
        close(client);
        return -1;
    }

    //client_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    memcpy(&client_addr.sin_addr,h->h_addr,h->h_length);

    cout << inet_ntoa(client_addr.sin_addr)<<endl;
    cout << "Connecting...."<<endl;
    //connect the socket to the addr:connect the seerver
    int temp;
    if((temp = connect(client,(sockaddr *)&client_addr,sizeof(client_addr))) != 0)
    {
        perror("connect failed:");
        cout << temp<<endl;
        close(client);
        cout << inet_ntoa(client_addr.sin_addr)<<endl;
        return -1;
    }

    char send_data[1024];
    char recv_data[1024];

    int recv_leng;
    //memset(recv_data,0,sizeof(recv_data));

    //send data to the server..
    while(1)
    {
        cin >> send_data;
        memset(recv_data,0,sizeof(recv_data));
        while (1)
        {
            if(send(client,send_data,strlen(send_data),0) < 0)
            {
                perror("send over");
                 return -1;
            }
            if(strlen(send_data) <= 1024)
            break;
            //if((recv_leng = recv(client,recv_data,sizeof(recv_data),0) )< 0){printf("recv over"); return -1;}
            //recv_data[recv_leng] = '\0';

        }


        //cout << "message from server:"<<recv_data<<endl;
        




    }
    

    close(client);
    return 0;
}