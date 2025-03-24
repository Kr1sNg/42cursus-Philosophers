/* create 2 threads, splits primes array into 2 parts, sum up then send the total result back to main */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void	*routine(void *arg)
{
	int	index = *(int *)arg;
	int	sum = 0;

	for (int i = 0; i < 5; i++)
		sum += primes[index + i];
	printf("local sum: %i\n", sum);
	*(int *)arg = sum;
	return (arg);
}

int	main(int argc, char *argv[])
{
	pthread_t	th[2];
	
	for (int i = 0; i < 2; i++)
	{
		int *a = malloc(sizeof(int));
		*a = i * 5;
		if (pthread_create(&th[i], NULL, &routine, a) != 0)
		{
			perror("Failed to create thread\n");
			return (EXIT_FAILURE);
		}
	}
	int	globalSum = 0;
	for (int i = 0; i < 2; i++)
	{
		int *res;
		if (pthread_join(th[i], (void **)&res) != 0)
		{
			perror("Failed to join thread\n");
			return (EXIT_FAILURE);
		}
		globalSum += *res;
		free(res);
	}
	printf("Global Sum: %i\n", globalSum);
	return (0);
}
