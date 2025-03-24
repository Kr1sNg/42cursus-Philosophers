#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int mails = 0;
pthread_mutex_t	mutex;

void	*routine()
{
	for (int i = 0; i < 20000000; i++)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	pthread_t	th[4];
	int 		i;

	pthread_mutex_init(&mutex, NULL);
	for (i = 0; i < 4; i++)
	{
		if (pthread_create(&th[i], NULL, routine, NULL) != 0)
			return (EXIT_FAILURE);
		printf("Thread %d has started\n", i);
	}
	for (i = 0; i < 4; i++)
	{
		if (pthread_join(th[i], NULL) != 0)
			return (EXIT_FAILURE);
		printf("Thread %d has finised execution\n", i);
	}
	pthread_mutex_destroy(&mutex);
	printf("Number of mails: %i\n", mails);
	return (0);
}
