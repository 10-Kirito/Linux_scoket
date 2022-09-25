#include"Server_class.h"
#include"Server_class.cpp"

using namespace std;

int main(int argc,char *argv[])
{
    if(argc != 2)
    {
        printf("Usage : %s <port>\n",argv[0]);
        exit(1);
    }
    //creat the server
    Server server;
    if(!server.InitServer(argv[1])) return 0;

    //acquire the fd of the server
    int fd_max = server.getServerfd();
    int server_fd = fd_max;

    //initialize
    struct timeval timeout;
    fd_set reads,cpy_reads;
    FD_ZERO(&reads);
    FD_SET(fd_max,&reads);
    int fd_num;//be used to store the return of the select

    while (1)
    {
        cpy_reads = reads;//store the reads to use next time
        timeout.tv_sec = 5;
        timeout.tv_usec = 5000;
        
        if((fd_num = select(fd_max + 1,&cpy_reads,0,0,&timeout))== -1)
            break;
        if(fd_num == 0)
            continue;

        //connecting and recv and read
        //express some fd change
        for(int i = 0;i < fd_max + 1;i++)
        {
            if(FD_ISSET(i,&cpy_reads))
            {
                if(i==server_fd)//connection request
                {
                    if(!server.Accept())
                        break;
                    else
                        printf("The client %s has connectted!\n",server.getClientIP());
                    FD_SET(server.getClientfd(),&reads);
                    if(fd_max < server.getClientfd())
                        fd_max = server.getClientfd();
                }
                else//read message
                {
                    int strlen;
                    char recvdata[1024];
                    memset(recvdata,0,1024);
                    strlen = read(i,recvdata,1024);
                    if(strlen == 0)
                    {
                        FD_CLR(i,&reads);
                        close(i);
                        printf("closed client: %d \n",i);
                    }
                    else
                    {
                        write(i,recvdata,strlen);
                    }



                }
            }
        }
    }
    return 0;
}
