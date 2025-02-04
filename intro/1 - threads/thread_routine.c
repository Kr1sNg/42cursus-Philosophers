
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *routine1()
{
	printf("Test from threads 1\n");
	sleep(3);
	printf("Ending thread 1\n");
}

void *routine2()
{
	printf("Test from threads 2\n");
	sleep(3);
	printf("Ending thread 2\n");
}

int	main(int argc, char *argv[])
{
	pthread_t	t1, t2;

	if (pthread_create(&t1, NULL, &routine1, NULL) != 0) //return 0 if the call completes successfully
		return (-42);
	if (pthread_create(&t2, NULL, &routine2, NULL) != 0)
		return (-42);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	return (0);
}




