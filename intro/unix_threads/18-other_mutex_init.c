// we can use PTHREAD_MUTEX_INITIALIZER instead of mutex_init and mutex_destroy

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define THREAD_NUM 2

pthread_mutex_t	mutexFuel = PTHREAD_MUTEX_INITIALIZER;

void *routine(void *args)
{
	printf("Routine\n");

	return (NULL);
}

int	main(int argc, char *argv[])
{
	pthread_t	th[THREAD_NUM];
	int			i;

	for (i = 0; i < THREAD_NUM; i++)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
			perror("Failed!\n");
	}

	for (i = 0; i < THREAD_NUM; i++)
	{
		if (pthread_join(th[i], NULL) != 0)
			perror("Failed!\n");
	}
	return (0);
}