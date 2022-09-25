    #include<stdio.h>
    #include<unistd.h>
    #include<sys/time.h>
    #include<sys/select.h>
    #define BUF_SIZE 30

    int main(int argc,char *argv[])
    {
        fd_set reads,temps;//temp is used to store the reads
        int result,strlen;
        char buff[BUF_SIZE];
        struct timeval timeout;

        FD_ZERO(&reads);//set the fd_set to the zero
        FD_SET(0,&reads);//set the standard input

        while (1)
        {
            temps = reads;
            timeout.tv_sec = 5;
            timeout.tv_usec = 0;
            result = select(1,&temps,0,0,&timeout);

            if(result == -1)//wrong
            {
                puts("select() error!");
                break;
            }
            else if(result == 0)//time out
            {
                puts("time out!");
            }
            else//normal
            {
                if(FD_ISSET(0,&temps))
                {
                    strlen = read(0,buff,BUF_SIZE);
                    buff[strlen] = 0;
                    printf("message from console: %s",buff);

                }

            }
        }
        
        return 0;
    }


