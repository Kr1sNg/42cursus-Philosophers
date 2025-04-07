#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>

void	*roll_dice()
{
	int value = (rand() % 6) + 1;
	int	*res = malloc(sizeof(int));
	*res = value;
	printf("%d\n", value);
	printf("%p\n", res);
	return (void *)res;
}

int	main(int argc, char **argv)
{
	pthread_t	th;
	int			*res;
	
	if (pthread_create(&th, NULL, &roll_dice, NULL) != 0)
		return (EXIT_FAILURE);
	if (pthread_join(th, (void **)&res) != 0) // second argument send the result (by double pointer from roll_dice)
		return (EXIT_FAILURE);
	printf("Result: %d\n", *res);
	printf("Main: %p\n", res);
	free(res);
	return (0);
}
