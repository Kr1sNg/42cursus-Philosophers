#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

// chefs = threads
// stove = shared data (+mutex)

pthread_mutex_t	stoveMutex[4];
int	stoveFuel[4] = {100, 100, 100, 100};

void	*routine(void *arg)
{
	for (int i = 0; i < 4; i++)
	{
		if (pthread_mutex_trylock(&stoveMutex[i]) == 0)
		{
			int fuelNeeded = (rand() % 30);
			if (stoveFuel[i] - fuelNeeded < 0)
				printf("No more fuel!\n");
			else
			{
				stoveFuel[i] -= (rand() % 30);
				usleep(500000);
				printf("Fuel left %d\n", stoveFuel[i]);
			}
			pthread_mutex_unlock(&stoveMutex[i]);
			break;
		}
		else
		{
			if (i == 3)
			{
				printf("no stove available yet, waiting...\n");
				usleep(300000);
				i = 0;
			}
		}
	}
	return (NULL);
}

int	main(int argc, char *argv[])
{
	pthread_t	th[10];

	srand(time(NULL));
	for (int i = 0; i < 4; i++)
		pthread_mutex_init(&stoveMutex[i], NULL);
	for (int i = 0; i < 10; i++)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
		{
			perror("Failed to create thread\n");
			return (EXIT_FAILURE);
		}
	}
	for (int i = 0; i < 10; i++)
	{
		if (pthread_join(th[i], NULL) != 0)
		{
			perror("Failed to join thread\n");
			return (EXIT_FAILURE);
		}
	}
	for (int i = 0; i < 4; i++)
		pthread_mutex_destroy(&stoveMutex[i]);
	return (0);
}
