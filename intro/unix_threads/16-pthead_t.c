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
	pthread_t th;

	(void)args;
	th = pthread_self();
	printf("%lu\n", (unsigned long)(uintptr_t)th);
	//printf("%d\n", (pid_t) syscall(SYS_gettid)); // linux
	printf("mach_thread_self: %u\n", mach_thread_self());
	
	return (NULL);
}

int	main(int ac, char *av[])
{
	pthread_t	th[THREAD_NUM];
	int			i;

	for (i = 0; i < THREAD_NUM; i++)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
			perror("Failed to create thread");
	}
	for (i = 0; i < THREAD_NUM; i++)
	{
		if (pthread_join(th[i], NULL) != 0)
			perror("Failed to join thread");
	}
	return (0);
}