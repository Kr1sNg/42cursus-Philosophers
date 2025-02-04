#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <pthread.h>

/* PROCESSES */ // -> return 2 process ids => don't share memory
// int	main(int argc, char *argv[])
// {
// 	// create 2 processes:
// 	int pid = fork();
// 	if (pid == -1)
// 		return 1;
// 	printf("Process is %i\n", getpid());
// 	if (pid != 0)
// 		wait (NULL);
// 	return (0);
// }


/* THREADS */ // -> return 1 process id => multi-threads => threads share the memory
void *routine()
{
	printf("Process id is %i\n", getpid());
}

int main(int argc, char *argv[])
{
	pthread_t t1, t2;

	if (pthread_create(&t1, NULL, &routine, NULL)) // return 0 if successfully running
		return 1;
	if (pthread_create(&t2, NULL, &routine, NULL))
		return 2;
	
	if (pthread_join(t1, NULL))
		return 3;
	if (pthread_join(t2, NULL))
		return 4;

	return 0;
}

