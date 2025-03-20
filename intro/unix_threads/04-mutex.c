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
	pthread_t	t1;
	pthread_t	t2;
	pthread_t	t3;
	pthread_t	t4;

	pthread_mutex_init(&mutex, NULL);
	if (pthread_create(&t1, NULL, routine, NULL) != 0)
		return (EXIT_FAILURE);
	if (pthread_create(&t2, NULL, routine, NULL) != 0)
		return (EXIT_FAILURE);
	if (pthread_create(&t3, NULL, routine, NULL) != 0)
		return (EXIT_FAILURE);
	if (pthread_create(&t4, NULL, routine, NULL) != 0)
		return (EXIT_FAILURE);
	if (pthread_join(t1, NULL) != 0)
		return (EXIT_FAILURE);
	if (pthread_join(t2, NULL) != 0)
		return (EXIT_FAILURE);
	if (pthread_join(t3, NULL) != 0)
		return (EXIT_FAILURE);
	if (pthread_join(t4, NULL) != 0)
		return (EXIT_FAILURE);
	pthread_mutex_destroy(&mutex);
	printf("Number of mails: %i\n", mails);
	return (0);
}

/* sometime the total received mails are not enough 200000, it was caused by the race condition
while thread t1 was running the routine, but thread t2 also updated variable mails */