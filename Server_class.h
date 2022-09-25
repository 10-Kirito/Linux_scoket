#ifndef _SERVER_H_
#define _SERVER_H_

#include<sys/socket.h>
#include<sys/types.h>
#include<sys/errno.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<sys/select.h>
#include<time.h>

#include<stdio.h>
#include<string.h>
#include<iostream>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>


class Server
{
private:
    struct sockaddr_in clientaddr;
    struct sockaddr_in serveraddr;
    int listenfd;
    int clientfd;
public:

    Server();
    ~Server();
    int getClientfd(){return clientfd;}
    int getServerfd(){return listenfd;}
    bool InitServer(char * port);//if listen successfully,return true,else return false
    bool Accept();
    char * getClientIP();
    bool readDta(const int sockfd,char * buffer,const size_t n);
    bool sendData(const int sockfd,char *buffer,int length);
    void closeClientFd(){ close(clientfd);}
    void closeServerFd(){ close(listenfd);}
};

#endif