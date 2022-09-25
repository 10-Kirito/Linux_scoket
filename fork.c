#include<stdio.h>
#include<unistd.h>

int gval = 10;
int main()
{
	pid_t pid;
	int lval = 20;
	gval++,lval+=5;
	pid = fork();

	if(pid == 0)
	{
		printf("I'm the children!\n");
		gval += 2,lval += 2;
	}
	else
	{
		gval-=2,lval -= 2;
		printf("I'm the father\n");
	}

	if(pid == 0)
		printf("Child proc: gval = %d, lval = %d\n",gval,lval);
	else
		printf("Parent proc: gval = %d, lval = %d\n",gval,lval);


	return 0;
}
