#include"server_finally.h"
using namespace std;

Server::Server()
{
    listenfd = -1;
    for(int i = 0;i < CLIENT_MAX;i++)
    {    
        client_socks[i] = -1;
        //cout << client_socks[i]<<endl;
    }
    for(int i = 0;i < CLIENT_MAX;i++)
        names[i] = "NULL";
}

Server::~Server()
{
    if(listenfd != -1)
        close(listenfd);
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

bool Server::Accept(int temp)
{
   
    int clien_len = sizeof(clientaddr[temp]);
    if(listenfd == -1) 
        return false;
    if((client_socks[temp] = accept(listenfd,(struct sockaddr*) &clientaddr[temp],(socklen_t *)&clien_len)) < 0)
    {
        client_socks[temp] = -1;
        return false;
    }
    //printf("The client %s has connectted!\n",inet_ntoa(clientaddr.sin_addr));
    return true;
}

int Server::findUser(string name)
{
    for(int i = 0;i < CLIENT_MAX;i++)
    {
        if(names[i] == name)
            return i;
    }
    return -1;
}

