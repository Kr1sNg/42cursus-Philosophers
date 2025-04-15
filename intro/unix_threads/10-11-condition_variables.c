#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

pthread_mutex_t mutexFuel;
pthread_cond_t	condFuel;

int	fuel = 0;

void *fuel_filling(void *arg)
{
	for (int i = 0; i < 5; i++)
	{
		pthread_mutex_lock(&mutexFuel);
		fuel += 30;
		printf("Filled fuel... %d\n", fuel);
		pthread_mutex_unlock(&mutexFuel);
		// pthread_cond_signal(&condFuel); //use when there's only one thread
		pthread_cond_broadcast(&condFuel); //when there's many thread
		sleep(1);
	}
	return (NULL);
}

void *car(void *arg)
{
	pthread_mutex_lock(&mutexFuel);
	while (fuel < 40)
	{
		printf("Not enough fuel\n");
		pthread_cond_wait(&condFuel, &mutexFuel);
		// equivalent to
		// pthread_mutex_unlock(&mutexFuel);
		// then wait for signal on condFuel
		// pthread_mutex_lock(&mutexFuel);
	}
	fuel -= 40;
	printf("Got fuel. Now left: %d\n", fuel);
	pthread_mutex_unlock(&mutexFuel);
	return (NULL);
}

int main(int ac, char *av[])
{
	pthread_t th[6];
	pthread_mutex_init(&mutexFuel, NULL);
	pthread_cond_init(&condFuel, NULL);
	for (int i = 0; i < 6; i++)
	{
		if (i == 4 || i == 5)
		{
			if (pthread_create(&th[i], NULL, &fuel_filling, NULL) != 0)
				perror("Failed to create thread");
		}
		else
		{
			if (pthread_create(&th[i], NULL, &car, NULL) != 0)
				perror("Failed to create thread");
		}
	}
	for (int i = 0; i < 6; i++)
	{
		if (pthread_join(th[i], NULL) != 0)
			perror("Failed to join thread");
	}
	pthread_mutex_destroy(&mutexFuel);
	pthread_cond_destroy(&condFuel);
	return (0);
}
