// detached threads from main, so we can't join them to the main

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <sys/syscall.h> // linux
#include <mach/mach.h> // for mac

#define THREAD_NUM 2

void *routine(void *args)
{
	sleep(1);
	printf("Finished execution\n");

	return (NULL);
}

int	main(int ac, char *av[])
{
	pthread_t	th[THREAD_NUM];
	pthread_attr_t	detachedThread;
	int			i;

	pthread_attr_init(&detachedThread);
	pthread_attr_setdetachstate(&detachedThread, PTHREAD_CREATE_DETACHED);

	for (i = 0; i < THREAD_NUM; i++)
	{
		if (pthread_create(&th[i], &detachedThread, &routine, NULL) != 0)
			perror("Failed to create thread");
		
		pthread_detach(th[i]);
	}
	for (i = 0; i < THREAD_NUM; i++)
	{
		if (pthread_join(th[i], NULL) != 0)
			perror("Failed to join thread");
	}

	pthread_attr_destroy(&detachedThread);
	// return (0); //-> main won't wait for other threads to finish executing 
	pthread_exit(0); // -> wait for threads finishing
}