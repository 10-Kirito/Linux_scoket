#include "server_finally.h"
#include "server_finally.cpp"
void * handle_clnt(void *arg);
void * recvdata(void *arg);
void * recvfile(void *arg);
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
    while(1)
    {
        if(!server.Accept(clnt_cnt))
            continue;
        printf("the client%s connect.\n",inet_ntoa(server.clientaddr[clnt_cnt].sin_addr));
        int temp = clnt_cnt;
        pthread_create(&t_id,NULL,handle_clnt,(void *)&temp);
        pthread_join(t_id,NULL);
        pthread_detach(t_id);
        clnt_cnt++;
    }
    return 0;
}

void * handle_clnt(void *arg)
{   
    int num = *((int *)arg);
    int client = server.client_socks[num];
    pthread_t t_id;
    char send_data[1024];
    pthread_mutex_init(&mutex,NULL);
    pthread_create(&t_id,NULL,recvdata,(void *)&num);

    //send t"he data to the client
    while(1)
    {
        cout << "please input:";
        cin >> send_data;
        write(client,send_data,strlen(send_data));
    }
    pthread_join(t_id,NULL);
    pthread_detach(t_id);
    return NULL;
}

void * recvdata(void *arg)
{
    //recv the normal message
    int num = *((int *)arg);
    int client = server.client_socks[num];
    pthread_t t_id;
    char recv_data[1024];
    memset(recv_data,0,1024);
    pthread_mutex_init(&mutex,NULL);
    pthread_create(&t_id,NULL,recvfile,(void *)&num);
    
    //send t"he data to the client
    while(1)
    {
        memset(recv_data,0,1024);
        read(client,recv_data,1024);
        if(strlen(recv_data) != 0)
            cout << "message from "<<inet_ntoa(server.clientaddr[num].sin_addr)<< " : " <<recv_data<<endl;
    }
    pthread_join(t_id,NULL);
    pthread_detach(t_id);
    return NULL;
}


void * recvfile(void *arg)
{
    int socketfd;
    if((socketfd = socket(AF_INET,SOCK_STREAM,0)) == -1) 
    {
        perror("S_Scoket create failed:"); 
    }
    struct sockaddr_in servaddr;
    memset(&servaddr,0,sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(atoi("2222"));
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(socketfd,(sockaddr *)&servaddr,sizeof(servaddr)) != 0) 
    {
        perror(" Recvfile Bind failed:");
        close(socketfd); 
    }
    int opt = 1;
    unsigned int len = sizeof(opt);
    setsockopt(socketfd,SOL_SOCKET,SO_REUSEADDR,&opt,len);
    if(listen(socketfd,4) != 0)
    {
        perror("Recvfile Listen failed:");
        close(socketfd); 
    };
    int clientfd;
    struct sockaddr_in clienaddr;
    int clien_len = sizeof(clienaddr);
    if((clientfd = accept(socketfd,(sockaddr*) &clienaddr,(socklen_t *)&clien_len)) < 0)
    {
        cout <<"Recvfile connect the file failed"<<endl;
    }
    //cout << "the num_fd of the clientfd is "<<clientfd<<endl<<socketfd<<endl;
    //cout <<endl<<"ready to accept the file"<<endl;
    char head[50];
    // @liuyuan
    //read(clientfd, stdout, 1024 * 4);
    read(clientfd,head,sizeof(head));
    //analysis the head of the file
    string temp = head;
    int pos = temp.find('&');
    string temp_1 = temp.substr(0,pos);
    string temp_2 = temp.substr(pos + 1);
    int size = stoi(temp_2);
    //cout << size<<endl;
    int count = 0;
    char *reply = "OK";
    write(clientfd,reply,strlen(reply));
    bool flag = true;
    FILE *file = NULL;
    file = fopen(temp_1.c_str(),"wb");
    char data[1024];
    if(!file)
    {
        cout << "create file "<<temp_1<<" failed"<<endl;
        return NULL;
    }

    while(flag)
    {
        memset(data,0,1024);
        count += read(clientfd,data,sizeof(data));
        //cout << count << endl;
        //cout << data<<endl;
        fprintf(file,"%s",data);
        
        if(count == size)
        {
            cout << "finish"<<endl;
            break;
        }
    fclose(file);
    close(clientfd);
    close(socketfd);
    return NULL;
}





// void * handle(void *arg)
// {
//     int num = *((int *) arg);
//     int client = server.client_socks[0];
//     int talker_fd;
//     char recvdata[1024];
//     memset(recvdata,0,1024);
//     string talker;
//     int temp0;
//     while(read(server.client_socks[clnt_cnt],&talker,sizeof(talker)) != 0){}
//     if((temp0 = server.findUser(talker)) == -1)
//         cout << "the user "<<talker<<" is not online"<<endl;
//     else
//         talker_fd = server.client_socks[temp0];

//     int str_len;

//     while((str_len = read(client,recvdata,1024))!=0)
//         write(talker_fd,recvdata,strlen(recvdata));

//     pthread_mutex_lock(&mutex);
//     for(int i = 0;i < clnt_cnt;i++)
//     {
//         if(client == server.client_socks[i])
//         {
//             while(i++<clnt_cnt - 1)
//             {
//                 server.client_socks[i] = server.client_socks[i +1];
//                 server.clientaddr[i] = server.clientaddr[i + 1];
//                 server.names[i] = server.names[i +1];
//             }
//             break;
//         }
//     }
//     clnt_cnt--;
//     pthread_mutex_unlock(&mutex);
//     close(client);
//     return NULL;
// }