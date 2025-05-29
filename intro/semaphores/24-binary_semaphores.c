/*
on Macbook:
cannot use sem_init, sem_destroy
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>  // For O_CREAT, O_EXCL

#define THREAD_NUM 4

sem_t *semFuel;
int *fuel;

void *routine(void *args)
{
	*fuel += 50;
	printf("Current value is %d\n", *fuel);
	sem_post(semFuel);
	return NULL;
}

int main(void)
{
	pthread_t th[THREAD_NUM];
	int i;

	fuel = malloc(sizeof(int));
	*fuel = 50;

	sem_unlink("/semaphore");
	// Open a named semaphore with initial value 1
	if ((semFuel = sem_open("/semaphore", O_CREAT | O_EXCL, 0644, 0)) == SEM_FAILED)
	{
		perror("sem_open");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < THREAD_NUM; i++)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
			perror("Failed to create thread");
	}
	sem_wait(semFuel);
	printf("deallocated fuel\n");
	free(fuel);

	for (i = 0; i < THREAD_NUM; i++)
	{
		if (pthread_join(th[i], NULL) != 0)
			perror("Failed to join thread");
	}

	if (sem_close(semFuel) == -1)
	{
		perror("sem_close");
		exit(EXIT_FAILURE);
	}
	if (sem_unlink("/semaphore") == -1)
	{
		perror("sem_unlink");
		exit(EXIT_FAILURE);
	}
	return 0;
}
