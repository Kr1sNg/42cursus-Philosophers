#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t ugly_gun;
pthread_mutex_t bad_gun;

typedef struct s_cowboy
{
	char			*name;
	unsigned long	react_time; //how fast the cowboy take the gun
	pthread_t		thread;
}				t_cowboy;


// DEADLOCK
// void *action(void *data)
// {
// 	t_cowboy cowboy;

// 	cowboy =  *(t_cowboy *)data;
// 	if (!strcmp(cowboy.name, "ugly"))
// 		pthread_mutex_lock(&ugly_gun);
// 	else
// 		pthread_mutex_lock(&bad_gun);
// 	printf("%s has taken his own gun\n", cowboy.name);

// 	// take the other gun
// 	//THIS IS WHERE DEADLOCK
// 	if (!strcmp(cowboy.name, "ugly"))
// 		pthread_mutex_lock(&bad_gun);
// 	else
// 		pthread_mutex_lock(&ugly_gun);
// 	printf("%s has taken the other's gun\n", cowboy.name);

// 	return (NULL);
// }

void *action(void *data)
{
	t_cowboy cowboy;

	cowboy =  *(t_cowboy *)data;

	// How fast the cowboy is
	printf("%s reaction_time %lu\n", cowboy.name, cowboy.react_time);
	usleep(cowboy.react_time);

	if (!strcmp(cowboy.name, "ugly"))
		pthread_mutex_lock(&ugly_gun);
	else
		pthread_mutex_lock(&bad_gun);
	printf("%s has taken his own gun\n", cowboy.name);

	// take the other gun
	//THIS IS WHERE DEADLOCK
	if (!strcmp(cowboy.name, "ugly"))
		pthread_mutex_lock(&bad_gun);
	else
		pthread_mutex_lock(&ugly_gun);

	printf("%s has taken the other's gun\n", cowboy.name);
	exit(EXIT_SUCCESS);
	return (NULL);
}


int main()
{
	srand(time(NULL) * getpid()); // take random value for timer
	t_cowboy	ugly = {"ugly", rand() % 10000};
	t_cowboy	bad = {"bad", rand() % 10000};

	pthread_mutex_init(&ugly_gun, NULL);
	pthread_mutex_init(&bad_gun, NULL);

	pthread_create(&ugly.thread, NULL, action, &ugly);
	pthread_create(&bad.thread, NULL, action, &bad);

	pthread_join(ugly.thread, NULL);
	pthread_join(bad.thread, NULL);


}

