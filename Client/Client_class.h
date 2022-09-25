#ifndef _CLIENT_H_
#define _CLIENT_H_

#include<sys/socket.h>
#include<sys/types.h>
#include<sys/errno.h>
#include<arpa/inet.h>
#include<netdb.h>

#include<string.h>
#include<iostream>
#include<unistd.h>
#include<stdlib.h>


class Client
{
private:
    int clientfd;
    struct sockaddr_in serveraddr;
    
public:

    Client();
    ~Client();
    int getClientfd(){return clientfd;}
    bool Connect(const char * serverip,const int port);
    char * getServerIP();
    int getClientip(){ return clientfd;};
    bool readDta(const int sockfd,char * buffer,const size_t n);
    bool sendData(const int sockfd,char *buffer,int length);
};

#endif