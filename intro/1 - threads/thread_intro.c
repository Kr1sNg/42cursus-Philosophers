
/*
**	Example of using threads in C with the pthread.h library (POSIX thread library)
*/

#include <stdio.h>
#include <pthread.h>

void	*computation(void *add);

int	main()
{
	pthread_t	thread1;
	pthread_t	thread2;

	long	value1 = 5;
	long	value2 = 2;


//  run with single thread:
// 
// 	computation((void *) &value1);
// 	computation((void *) &value2);
//
//
//	this is consider as a single thread too:

	// pthread_create(&thread1, NULL, computation, (void *)&value1);
	// pthread_join(thread1, NULL);
	// pthread_create(&thread2, NULL, computation, (void *)&value2);
	// pthread_join(thread2, NULL);
	
// this is multiple threads:	

	pthread_create(&thread1, NULL, computation, (void *)&value1);
	pthread_create(&thread2, NULL, computation, (void *)&value2);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	return (0);
}

void	*computation(void *add)
{
	long sum = 0;

	long *add_num = (long *)add;
	for (long i = 0; i < 100000000; i++)
		sum += *add_num;
		printf("%ld\n", sum);

	return (NULL);
}


/* -> check the time run:
**		$ time ./a.out
** -> we can see when running with a single thread: time run is about 0.49s
** -> running with multiple threads: time run is about 0.26s
*/