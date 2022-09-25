#include<stdio.h>
#include<string.h>
#include<unistd.h>
#define BUF_SIZE 30

int main()
{
	int fds[2];
	char str[]="Who are you?";
	char str0[]="I'm your father!";

	char buff[BUF_SIZE];
	pid_t pid;

	pipe(fds);
	pid = fork();
	if(pid == 0)
	{
		write(fds[1],str,sizeof(str));
		//sleep(2);
		read(fds[0],buff,BUF_SIZE);
		printf("buff from father:");
		puts(buff);//puts is end of '\0'
	}
	else
	{
		//write(fds[1],str0,strlen(str0));

		read(fds[0],buff,BUF_SIZE);
		printf("buff from son:");
		puts(buff);
		write(fds[1],str0,sizeof(str0));
		sleep(3);
	}

	return 0;
}
