
// system can only handle maximum 12 people to login at the same time

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>


#define THREAD_NUM 16 // people try to connect to the system

sem_t	semaphore;

void *routine(void *args)
{
	printf("(%d) waiting in the login queue\n", *(int *)args);
	sem_wait(&semaphore);
	printf("(%d) logged in\n", *(int *)args);
	sleep(rand() % 5 + 1); // time the user stays randomly onto the system
	printf("(%d) logged out\n", *(int *)args);
	sem_post(&semaphore);
	free(args);
	return (NULL);
}

int	main(int ac, char *av[])
{
	pthread_t	th[THREAD_NUM];
	int			i;

	sem_init(&semaphore, 0, 12); // the last: value to set to semaphore

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
