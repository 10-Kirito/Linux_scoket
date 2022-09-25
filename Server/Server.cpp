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
    //sever_socket
    int socketfd;
    if((socketfd = socket(AF_INET,SOCK_STREAM,0)) == -1) 
    {
        perror("S_Scoket create failed:"); 
        return -1; 
    }
    //bind the addr to scoketfd
    struct sockaddr_in servaddr;
    memset(&servaddr,0,sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(atoi("2222"));
    //servaddr.sin_addr.s_addr = inet_addr("192.168.222.129");
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(socketfd,(sockaddr *)&servaddr,sizeof(servaddr)) != 0) 
    {
        perror("Bind failed:");
        close(socketfd); 
    }

    //set SO_REUSEADDR
    int opt = 1;
    unsigned int len = sizeof(opt);
    setsockopt(socketfd,SOL_SOCKET,SO_REUSEADDR,&opt,len);
    cout << "listening"<<endl;
    //listening....
    if(listen(socketfd,4) != 0)
    {
        perror("Listen failed:");
        close(socketfd); 
    };

    //accepting....
    int clientfd;
    //the addr of client
    struct sockaddr_in clienaddr;
    int clien_len = sizeof(clienaddr);
    clientfd = accept(socketfd,(sockaddr*) &clienaddr,(socklen_t *)&clien_len);

    printf("The client %s has connectted!\n",inet_ntoa(clienaddr.sin_addr));

    //recv the data from the client...

    char buf[1024];
    memset(buf,0,sizeof(buf));
    //receive the data finished
    char send_buf[1024];
    while(1)
    {
        int recvlen = recv(clientfd,buf,sizeof(buf),0);
        if(recvlen <= 0 || recvlen <= 1024) break;//over
        buf[recvlen] = '\0';
        printf("receive from client: %s\n",buf);
        // scanf("please reply:%s",send_buf);
        // int send_len = sizeof(send_buf);
        // if(send(clientfd,send_buf,send_len,0) <= 0) 
        // {
        //     perror("send failed:"); 
        //     break;
        // };

    }
    close(socketfd);
    close(clientfd);

    return 0;
}