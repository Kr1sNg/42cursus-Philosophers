#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int mails = 0;

void	*routine()
{
	for (int i = 0; i < 10000; i++)
		mails++;
	return (NULL);
}

int	main(int argc, char **argv)
{
	pthread_t	t1;
	pthread_t	t2;

	if (pthread_create(&t1, NULL, routine, NULL) != 0)
		return (EXIT_FAILURE);
	if (pthread_create(&t2, NULL, routine, NULL) != 0)
		return (EXIT_FAILURE);
	if (pthread_join(t1, NULL) != 0)
		return (EXIT_FAILURE);
	if (pthread_join(t2, NULL) != 0)
		return (EXIT_FAILURE);
	printf("Number of mails: %i\n", mails);
	return (0);
}