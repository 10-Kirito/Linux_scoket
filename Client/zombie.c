#include<stdio.h>
#include<unistd.h>
#include<signal.h>
void test(int sig)
{
	if(sig == SIGCHLD)
		puts("use signal to end child");

	return;
}


int main()
{
	struct sigaction act;
	act.sa_handler = test;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGCHLD,&act,0);

	pid_t pid = fork();
	if(pid == 0)//children
		puts("Children!\n");
	else
	{
		printf("Child Process ID:%d \n",pid);
		sleep(30);
	}

	if(pid == 0)
		puts("End child process");
	else
		puts("End parent process");


	return 0;
}
