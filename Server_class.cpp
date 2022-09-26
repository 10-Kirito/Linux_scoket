#include"Server_class.h"
using namespace std;

Server::Server()
{
    listenfd = -1;
    clientfd = -1;
}

Server::~Server()
{
    if(listenfd != -1)
        close(listenfd);
    
    if(clientfd != -1)
        close(clientfd);
}

bool Server::InitServer(char *port)
{
    if((listenfd = socket(AF_INET,SOCK_STREAM,0)) == -1) 
    {
        perror("S_Scoket create failed:"); 
        return false; 
    }   

    //bind the addr to scoketfd
    memset(&serveraddr,0,sizeof(serveraddr));

    serveraddr.sin_family = AF_INET;
    //serveraddr.sin_port = htons(port);
    serveraddr.sin_port = htons(atoi(port));
    //serveraddr.sin_addr.s_addr = inet_addr("192.168.222.129");
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);


    int opt = 1;
    unsigned int len = sizeof(opt);
    setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&opt,len);
    if(bind(listenfd,(sockaddr *)&serveraddr,sizeof(serveraddr)) != 0) 
    {
        perror("Bind failed:");
        close(listenfd); 
        return false;
    }

    //listening....
    if(listen(listenfd,20) != 0)
    {
        perror("Listen failed:");
        close(listenfd); 
        return false;
    }
    //else
        //cout << "listen right"<<endl;
    
    return true;
}

bool Server::Accept()
{
   
    int clien_len = sizeof(clientaddr);
    if(listenfd == -1) 
        return false;
    //cout << "connecting..."<<endl;
    if((clientfd = accept(listenfd,(struct sockaddr*) &clientaddr,(socklen_t *)&clien_len)) < 0)
        return false;

    return true;
}
char * Server::getClientIP()
{
    string temp = "no client connented!";
    if(clientfd < 0)
        return (char *)temp.c_str();
    else
        return inet_ntoa(clientaddr.sin_addr);
}

bool Server::readDta(const int sockfd,char *buffer,const size_t n)
{
    memset(buffer,0,1024);

    
    int readlen = recv(sockfd,buffer,n,0);
    if(readlen <= 0)
        return false;
    else
        return true;

}

bool Server::sendData(const int sockfd,char *buffer,int length)
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