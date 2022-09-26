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


    pthread_create(&t_id,NULL,recvfile,(void *)&clientfd);


    //send t"he data to the client
    while(1)
    {
        memset(recv_data,0,1024);
        read(client,recv_data,1024);
        if(strlen(recv_data) != 0)
            cout << "message from "<<inet_ntoa(server.clientaddr[num].sin_addr)<< " : " <<recv_data<<endl;
    }
    pthread_join(t_id,NULL);
    close(socketfd);
    close(clientfd);
    pthread_detach(t_id);
    return NULL;
}


void * recvfile(void *arg)
{
    int clientfd = *((int *)arg);
    
    //cout << "the num_fd of the clientfd is "<<clientfd<<endl<<socketfd<<endl;
    //cout <<endl<<"ready to accept the file"<<endl;
    //cout << "file_fd connect right"<<endl;
    char head[50];
    // @liuyuan
    //read(clientfd, stdout, 1024 * 4);
    read(clientfd,head,sizeof(head));
    //analysis the head of the file
    string temp = head;
    int pos = temp.find('&');
    string temp_1 = temp.substr(0,pos);
    string temp_2 = temp.substr(pos + 1);
    cout << temp_2<<endl;
    int size = stoi(temp_2,nullptr,10);
    cout << size<<endl;
    sleep(10);
    //cout << size<<endl;
    int count = 0;
    char *reply = "OK";
    write(clientfd,reply,strlen(reply));
    bool flag = true;
    FILE *file = NULL;
    file = fopen(temp_1.c_str(),"a+");
    char data[1024 * 2];
    if(!file)
    {
        cout << "create file "<<temp_1<<" failed"<<endl;
        return NULL;
    }

    while(flag)
    {
        memset(data,0,1024);
        count += read(clientfd,data,sizeof(data));
        cout << count <<endl;   
        fprintf(file,"%s",data);
        
        if(count == size)
        {
            cout << "finish"<<endl;
            break;
        }
    
    }


    fclose(file);
    close(clientfd);
    return NULL;
}