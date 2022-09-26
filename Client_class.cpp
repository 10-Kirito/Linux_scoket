#include"Client_class.h"
using namespace std;

Client::Client()
{
    clientfd = -1;
}

Client::~Client()
{
    if(clientfd != -1)
        close(clientfd);
}


bool Client::Connect(const char * serverip,const int port)
{

    if((clientfd = socket(AF_INET,SOCK_STREAM,0)) == -1) 
    {
        perror("C_Scoket create failed:"); 
        return false; 
    }   

    //bind the addr to scoketfd
    memset(&serveraddr,0,sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    //advanced put addr
    struct hostent * h;
    if((h = gethostbyname(serverip)) == 0)
    {
        printf("gethost failed!\n");
        close(clientfd);
        return false;
    }

    //serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    memcpy(&serveraddr.sin_addr,h->h_addr,h->h_length);
    //cout << inet_ntoa(serveraddr.sin_addr)<<endl;
    int temp;
    if((temp = connect(clientfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr)))!= 0)
    {
        perror("connect failed:");
        cout << temp<<endl;
        close(clientfd);
        //cout << inet_ntoa(serveraddr.sin_addr)<<endl;
        return false;
    }
    return true;
}
char * Client::getServerIP()
{
    string temp = "Connented failed!";
    if(clientfd < 0)
        return (char *) temp.c_str();
    else
        return inet_ntoa(serveraddr.sin_addr);
}

bool Client::readDta(const int sockfd,char *buffer,const size_t n)
{
    int readlen = recv(sockfd,buffer,n,0);
    if(readlen <= 0)
        return false;
    else
        return true;

}

bool Client::sendData(const int sockfd,char *buffer,int length)
{
    int sum = length;
    int written;
    int count = 0;
    while(sum > 0)
    {
        written = send(sockfd,buffer + count,sum,0);
        if(written <= 0)
            return false;
        sum -= written;
        count += written;
    }
    return true;
}