// How to pass arguments to threads in C
// Problem: Create 15 threads, each taking a unique prime from the primes array and print it.


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int primes[15] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};

void *routine(void *arg)
{
	int index = *(int *)arg;
	printf("%d \n", primes[index]);
	free(arg);
}


int main(int argc, char *argv[])
{
	pthread_t th[15];
	int i;
	for (i = 0; i < 15; i++)
	{
		int *a = malloc(sizeof(int));
		*a = i;
		if (pthread_create(&th[i], NULL, &routine, a))
			return (-42);
	}
	for (i = 0; i < 15; i++)
	{
		if (pthread_join(th[i], NULL))
			return (-42);
	}

	return 0;
}
