#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{
	printf("本进程的进程编号是：%d\n",getpid());
	sleep(30);
	return 0;
}

