#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>


int main()
{
	int status;
	pid_t pid = fork();

	if(pid == 0)
		return 1;
	else
	{
		printf("Children PID:%d \n",pid);
		pid = fork();
		if(pid == 0)
		{
			exit(6);
		}
		else
		{
			printf("Children PID:%d \n",pid);
			wait(&status);
			if(WIFEXITED(status))
				printf("child one send: %d \n",WEXITSTATUS(status));
			wait(&status);
			if(WIFEXITED(status))
				printf("child two send: %d \n",WEXITSTATUS(status));
			wait(&status);
			sleep(30);
		}
	}
	
	return 0;
}
