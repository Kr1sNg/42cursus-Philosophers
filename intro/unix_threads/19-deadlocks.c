// simple example of deadlock is when you lock a mutex twice

// => lock and unlock mutexes should be in order to avoid the deadlock

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define THREAD_NUM 8

pthread_mutex_t	mutexFuel;
int	fuel = 50;
pthread_mutex_t	mutexWater;
int water = 10;

void *routine(void *args)
{
	// pthread_mutex_lock(&mutexWater); // => could have a deadlock
	pthread_mutex_lock(&mutexFuel);
	pthread_mutex_lock(&mutexWater);
	fuel += 50;
	water = fuel;
	printf("Incremented fuel to: %d\n", fuel);
	printf("Set water to %d\n", water);
	pthread_mutex_unlock(&mutexFuel);
	pthread_mutex_unlock(&mutexWater);

	(void)args;
	return (NULL);
}

int	main(int ac, char *av[])
{
	pthread_t	th[THREAD_NUM];
	int			i;
	pthread_mutex_init(&mutexFuel, NULL);
	pthread_mutex_init(&mutexWater, NULL);

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
	printf("water: %d\n", water);
	pthread_mutex_destroy(&mutexFuel);
	pthread_mutex_destroy(&mutexWater);
	return (0);
}
