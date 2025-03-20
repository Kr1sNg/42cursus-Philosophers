/* example of processes to compare to threads */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int	main(int argc, char **argv)
{
	int x = 2;
	int	pid = fork();

	if (pid == -1)
		return (EXIT_FAILURE);
	printf("Process id %d\n", getpid());
	if (pid == 0)
		x++;
	sleep(2);
	printf("value of x: %d\n", x);
	if (pid != 0)
		wait(NULL);
	
	return (0);
}