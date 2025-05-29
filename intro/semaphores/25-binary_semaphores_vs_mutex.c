#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define THREAD_NUM 4

typedef	struct s_data
{
	// pthread_mutex_t mutexFuel;
	sem_t			*semFuel;
	int				fuel;
}	t_data;

void	*routine1(void *args)
{
	t_data	*data = (t_data *)args;

	while (1)
	{
		// pthread_mutex_lock(&data->mutexFuel);
		sem_wait(data->semFuel);
		data->fuel += 50;
		printf("Current value is %d\n", data->fuel);
	}
	return (NULL);
}

void	*routine2(void *args)
{
	t_data	*data = (t_data *)args;

	while (1)
	{
		// pthread_mutex_unlock(&data->mutexFuel);
		sem_post(data->semFuel);
		usleep(50000);
	}
}

int main(void)
{
	t_data		data;
	pthread_t	th[THREAD_NUM];
	int			i = -1;

	data.fuel = 50;
	// pthread_mutex_init(&data.mutexFuel, NULL);
	// sem_init -> sem_open
	sem_unlink("/semFuel");
	data.semFuel = sem_open("/semFuel", O_CREAT | O_EXCL, 0644, 0);
	if (data.semFuel == SEM_FAILED)
		perror("sem_open");

	while (++i < THREAD_NUM)
	{
		if (i % 2 == 0)
		{
			if (pthread_create(&th[i], NULL, &routine1, &data) != 0)
				perror("error create\n");
		}
		else
		{
			if (pthread_create(&th[i], NULL, &routine2, &data) != 0)
				perror("error create\n");
		}
	}
	i = -1;
	while (++i < THREAD_NUM)
	{
		if (pthread_join(th[i], NULL) != 0)
			perror("error create\n");
	}
	// pthread_mutex_destroy(&data.mutexFuel);
	// sem_destroy => sem_close && sem_unlink
	if (sem_close(data.semFuel) == -1)
		perror("sem_close");
	if (sem_unlink("/semFuel") == -1)
		perror("sem_unlink");
	
	return 0;
}
