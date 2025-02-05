#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int mails = 0;
pthread_mutex_t mutex;

void *routine()
{
	for (int i = 0; i < 1000000; i++)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
	}

}


int main(int argc, char *argv[])
{
	pthread_t th[8];
	int i;
	pthread_mutex_init(&mutex, NULL);
	for (i = 0; i < 8; i++)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0) //return 0 if the call completes successfully
		{
			perror("Failed to create thread");
			return (-42);		
		}
		printf("1 - Number of mail: %d\n", mails);
		printf("Thread %i has started\n", i);
	}

	for (i = 0; i < 8; i++) //have to separate thread_create and thread_join
	{
		if (pthread_join(th[i], NULL) != 0)
			return (-42);
		printf("2 - Number of mail: %d\n", mails);
		printf("Thread %i has finished execution\n", i);
	}

	pthread_mutex_destroy(&mutex);
	printf("Number of mail: %d\n", mails);
	
	return (0);
}