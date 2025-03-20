/* example of threads to compare to processes */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int x = 2;

void	*routine1()
{
	x++;
	sleep(2);
	printf("value of x: %d\n", x);
	return (NULL);
}

void	*routine2()
{
	sleep(2);
	printf("value of x: %d\n", x);
	return (NULL);
}

int	main(int argc, char **argv)
{
	pthread_t	t1;
	pthread_t	t2;

	if (pthread_create(&t1, NULL, routine1, NULL) != 0)
		return (EXIT_FAILURE);
	if (pthread_create(&t2, NULL, routine2, NULL) != 0)
		return (EXIT_FAILURE);
	if (pthread_join(t1, NULL) != 0)
		return (EXIT_FAILURE);
	if (pthread_join(t2, NULL) != 0)
		return (EXIT_FAILURE);
	return (0);
}