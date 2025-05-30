#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int mails = 0;
pthread_mutex_t mutex;



void *routine()
{
	for (int i = 0; i < 1000000; i++)
	{
		pthread_mutex_lock(&mutex); //protect a thread agaist other threads executing it in the same time 
		mails++;
		pthread_mutex_unlock(&mutex);
	}

}


int main(int argc, char *argv[])
{
	pthread_t p1, p2;
	pthread_mutex_init(&mutex, NULL);

	if (pthread_create(&p1, NULL, &routine, NULL) != 0) //return 0 if the call completes successfully
		return (-42);
	if (pthread_create(&p2, NULL, &routine, NULL) != 0)
		return (-42);

	if (pthread_join(p1, NULL))
		return (-42);
	if (pthread_join(p2, NULL))
		return (-42);
	pthread_mutex_destroy(&mutex);
	printf("Number of mail: %d\n", mails);
	
	return (0);
}
