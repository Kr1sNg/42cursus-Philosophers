// we don't really need to use sem_value because this value can't be trusted

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define THREAD_NUM 4

typedef struct s_data
{
	int			a;
	sem_t		*sem;
}	t_data;

void	*routine(void *args)
{
	t_data *data = (t_data *)args;
	
	sem_wait(data->sem);
	// data->a += 50;
	printf("new value %d\n", data->a);
	sem_post(data->sem);
	return (NULL);
}

int	main(void)
{
	pthread_t	th[THREAD_NUM];
	int			i = 0;
	t_data		data;

	sem_unlink("/sem");
	data.sem = sem_open("/sem", O_CREAT | O_EXCL, 0644, 4);
	if (data.sem == SEM_FAILED)
		perror("sem_open");

	while (i < THREAD_NUM)
	{
		data.a = i;
		printf("old a: %i\n", data.a);
		if (pthread_create(&th[i], NULL, &routine, &data) != 0)
			perror("error create thread");
		sleep(1);
		i++;
	}
	i = -1;
	while (++i < THREAD_NUM)
	{
		if (pthread_join(th[i], NULL) != 0)
			perror("error join");
	}
	if (sem_close(data.sem) == -1)
		perror("sem_close");
	if (sem_unlink("/sem") == -1)
		perror("sem_unlink");
	 
}