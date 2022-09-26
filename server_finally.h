#ifndef _SERVER_FINAL_H_
#define _SERVER_FINAL_H_

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
#define CLIENT_MAX 256

using namespace std;

class Server
{
private:
    struct sockaddr_in serveraddr;
    int listenfd;

    
public:
    
    struct sockaddr_in clientaddr[CLIENT_MAX];
    int client_socks[CLIENT_MAX];
    string names[CLIENT_MAX];
    Server();
    ~Server();
    // int getClientfd(int temp){return client_socks[temp];}
    // string getClientName(int temp){return names[temp];}
    // struct sockaddr_in getcliAddr(int temp){return clientaddr[temp];}
    bool InitServer(char * port);//if listen successfully,return true,else return false
    bool Accept(int temp);
    void setName(int temp,string name) { names[temp] = name;}
    int getclientfd(int temp){return client_socks[temp];}

    int findUser(string name);
};

#endif