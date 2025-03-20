#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void	*routine()
{
	printf("Test from threads\n");
	sleep(3);
	printf("Ending test\n");
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
	return (0);
}