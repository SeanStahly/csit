#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv, char ** env)
{
	pid_t p;
	int result = fork();
	if( result == 0)
	{
		p = getpid();
		printf("PID = %d\t", p);
		puts("Child");
		sleep(8);
	}
	else
	{
		p = getpid();
		printf("PID = %d\t", p);
		puts("Parent 1");
		wait(result);
		result = fork();
		if( result == 0 )
		{
			p = getpid();
			printf("PID = %d\t", p);
			puts("Child");
			sleep(5);
		}
		if( result > 0)
		{
			wait(result);
			puts("Parent2");
		}
	}
	return 0;
}
