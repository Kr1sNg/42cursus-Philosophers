#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>


#define THREAD_NUM 4

sem_t	semaphore;

void *routine(void *args)
{
	sem_wait(&semaphore);
	sleep(5);
	printf("hello from thread %d\n", *(int *)args);
	sem_post(&semaphore);
	free(args);
	return (NULL);
}

int	main(int ac, char *av[])
{
	pthread_t	th[THREAD_NUM];
	int			i;

	sem_init(&semaphore, 0, 1); // the last: value to set to semaphore

	for (i = 0; i < THREAD_NUM; i++)
	{
		int *a = malloc(sizeof(int));
		*a = i;
		if (pthread_create(&th[i], NULL, &routine, a) != 0)
			perror("Failed to create thread");
	}
	for (i = 0; i < THREAD_NUM; i++)
	{
		if (pthread_join(th[i], NULL) != 0)
			perror("Failed to join thread");
	}

	sem_destroy(&semaphore);
	return (0);
}