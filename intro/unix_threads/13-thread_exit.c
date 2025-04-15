// other way to return value of thread with pthread_exit

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>

void	*roll_dice()
{
	int value = (rand() % 6) + 1;
	int	*res = malloc(sizeof(int));
	*res = value;
	printf("Thread res: %d\n", value);
	printf("%p\n", res);
	pthread_exit((void *)res);
}

int	main(int argc, char **argv)
{
	pthread_t	th;
	int			*res;
	
	if (pthread_create(&th, NULL, &roll_dice, NULL) != 0)
		return (EXIT_FAILURE);
	// pthread_exit(0); // we can use pthread_exit in main() to wait the thread to finish before exit the process (the code below won't run)
	if (pthread_join(th, (void **)&res) != 0) // second argument send the result (by double pointer from roll_dice)
		return (EXIT_FAILURE);
	printf("Result: %d\n", *res);
	printf("Main: %p\n", res);
	free(res);
	return (0);
}
