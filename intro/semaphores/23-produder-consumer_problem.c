/* Producer - Consumer problem: shared memory (buffer)
	- producers supply the data to the buffer
	- consumers take the data from the buffer
	=> problems:
		1. manage shared memory access (avoid race condition)
		2. checking for if buffer is full (for producers to stop feeding the buffer)
		3. checking for if buffer is empty (for consumers to stop taking from the buffer)
		 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

#define THREAD_NUM 8

sem_t	semEmpty;
sem_t	semFull;

pthread_mutex_t	mutexBuffer;

int buffer[10];
int count = 0;

void *producer(void *args)
{
	while (1)
	{
		// produce
		int x = rand() % 100;
		sleep(1);

		// add to the buffer
		sem_wait(&semEmpty);
		pthread_mutex_lock(&mutexBuffer);
		buffer[count] = x;
		count++;

		pthread_mutex_unlock(&mutexBuffer);
		sem_post(&semFull);
	}
	return (NULL);
}

void *consumer(void *args)
{
	while (1)
	{
		int y;

		// remove from the buffer
		sem_wait(&semFull);
		pthread_mutex_lock(&mutexBuffer);
		y = buffer[count - 1];
		count--;

		pthread_mutex_unlock(&mutexBuffer);
		sem_post(&semEmpty);

		// consume
		printf("got %d\n", y);
		// sleep(1);
	}
	return (NULL);
}

int	main(int ac, char *av[])
{
	pthread_t	th[THREAD_NUM];
	int	i;

	srand(time(NULL));
	pthread_mutex_init(&mutexBuffer, NULL);
	sem_init(&semEmpty, 0, 10); // 0 bcs we have only 1 process (and 2 threads)
	sem_init(&semFull, 0, 0);
	for (i = 0; i < THREAD_NUM; i++)
	{
		if (i > 0)
		{
			if (pthread_create(&th[i], NULL, &producer, NULL) != 0)
				perror("Failed to create thread\n");
		}
		else
		{
			if (pthread_create(&th[i], NULL, &consumer, NULL) != 0)
				perror("Failed to create thread\n");
		}
	}
	for (i = 0; i < THREAD_NUM; i++)
	{
		if (pthread_join(th[i], NULL) != 0)
			perror("Failed to join thread\n");
	}
	sem_destroy(&semEmpty);
	sem_destroy(&semFull);
	pthread_mutex_destroy(&mutexBuffer);
	return (0);
}
