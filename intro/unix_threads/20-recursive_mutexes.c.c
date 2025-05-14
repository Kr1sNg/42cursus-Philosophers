// NOTICE: This mutex is locked and unlocked by only one thread (not one and other)


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define THREAD_NUM 8

pthread_mutex_t	mutexFuel;
int	fuel = 50;

void *routine(void *args)
{
	
	pthread_mutex_lock(&mutexFuel);
	pthread_mutex_lock(&mutexFuel); // without recursiveMutex attr, we will have a deadlock here
	// bcs we locked a mutex twice
	fuel += 50;
	printf("Incremented fuel to: %d\n", fuel);
	pthread_mutex_unlock(&mutexFuel);
	pthread_mutex_unlock(&mutexFuel);

	(void)args;
	return (NULL);
}

int	main(int ac, char *av[])
{
	pthread_t			th[THREAD_NUM];
	int					i;
	pthread_mutexattr_t recursiveMutex; // variable to help mutex can be locked multiple times inside a thread (recursive mutex)

	pthread_mutexattr_init(&recursiveMutex);
	pthread_mutexattr_settype(&recursiveMutex, PTHREAD_MUTEX_RECURSIVE_NP);
	pthread_mutex_init(&mutexFuel, &recursiveMutex);
	for (i = 0; i < THREAD_NUM; i++)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
			perror("Failed to create thread");
	}
	for (i = 0; i < THREAD_NUM; i++)
	{
		if (pthread_join(th[i], NULL) != 0)
			perror("Failed to join thread");
	}
	printf("Fuel: %d\n", fuel);
	pthread_mutexattr_destroy(&recursiveMutex);
	pthread_mutex_destroy(&mutexFuel);
	return (0);
}
