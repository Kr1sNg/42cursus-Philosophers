// How to sum numbers from an array
// Problem: Using thread to calculate the sum of an array


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int primes[16] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53};

void *routine(void *arg)
{
	int index = *(int *)arg;
	int sum = 0;
	for (int j = 0; j < 8; j++)
		sum += primes[index + j];
	printf("local sum: %i\n", sum);
	*(int *)arg = sum;
	return arg;
}


int main(int argc, char *argv[])
{
	pthread_t th[2];
	int i;
	for (i = 0; i < 2; i++)
	{
		int *a = malloc(sizeof(int));
		*a = i * 8;
		if (pthread_create(&th[i], NULL, &routine, a))
			return (-42);
	}
	int totalsum = 0;
	for (i = 0; i < 2; i++)
	{
		int *res;
		if (pthread_join(th[i], ((void**)&res)))
			return (-42);
		totalsum += *res;
		free(res);
	}
	printf("total sum: %d\n", totalsum);
	return 0;
}
