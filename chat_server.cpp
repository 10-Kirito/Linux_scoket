#include "server_finally.h"
#include "server_finally.cpp"
void * handle_clnt(void *arg);
void * handle(void *arg);
pthread_mutex_t mutex;
int clnt_cnt = 0;
//initialize the server

Server server;
using namespace std;
int main(int argc,char *argv[])
{
    
    
    if(argc != 2)
    {
        printf("Usage : %s <port> \n",argv[0]);
        exit(1);
    }
    if(!server.InitServer(argv[1]))
        return -1;
    //initialize the mutex
    pthread_t t_id;
    pthread_mutex_init(&mutex,NULL);
    char name_temp[50];
    while(1)
    {
        if(!server.Accept(clnt_cnt))
            continue;
        printf("the client%s connect.\n",inet_ntoa(server.clientaddr[clnt_cnt].sin_addr));
        int temp = clnt_cnt;
        pthread_create(&t_id,NULL,handle,(void *)&temp);
        pthread_detach(t_id);
        clnt_cnt++;
    }
    return 0;
}

void * handle_clnt(void *arg)
{
    int num = *((int *) arg);
    int client = server.client_socks[0];
    int talker_fd;
    char recvdata[1024];
    memset(recvdata,0,1024);
    string talker;
    int temp0;
    while(read(server.client_socks[clnt_cnt],&talker,sizeof(talker)) != 0){}
    if((temp0 = server.findUser(talker)) == -1)
        cout << "the user "<<talker<<" is not online"<<endl;
    else
        talker_fd = server.client_socks[temp0];

    int str_len;

    while((str_len = read(client,recvdata,1024))!=0)
        write(talker_fd,recvdata,strlen(recvdata));

    pthread_mutex_lock(&mutex);
    for(int i = 0;i < clnt_cnt;i++)
    {
        if(client == server.client_socks[i])
        {
            while(i++<clnt_cnt - 1)
            {
                server.client_socks[i] = server.client_socks[i +1];
                server.clientaddr[i] = server.clientaddr[i + 1];
                server.names[i] = server.names[i +1];
            }
            break;
        }
    }
    clnt_cnt--;
    pthread_mutex_unlock(&mutex);
    close(client);
    return NULL;
}


void * handle(void *arg)
{
    int num = *((int *) arg);
    int client = server.client_socks[num];
    char name[20];
    //assume we can read the name of the client
    read(client,name,sizeof(name));        


    //read the message of the client




    //recv the message of the other client


    return NULL;
}