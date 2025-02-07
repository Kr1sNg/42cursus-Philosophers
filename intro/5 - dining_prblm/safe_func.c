#include "dining.h"

void *safe_malloc(size_t bytes)
{
	void *ret;

	ret = malloc(bytes);
	if (ret == NULL)
		error_exit("Error with malloc");
	return (ret);
}

/* Controls on return status of mutex */

static void	handle_mutex_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	else
		error_exit("Error Mutex!");
}

/* Mutex safe */

void safe_mutex_handle(t_mtx *mutex, t_opcode opcode)
{
	if (opcode == LOCK)
		if (pthread_mutex_lock(mutex));	
	else if (opcode == UNLOCK)
		pthread_mutex_unlock(mutex);
	else if (opcode == INIT)
		pthread_mutex_init(mutex, NULL);
	else if (opcode == DESTROY)
		pthread_mutex_destroy(mutex);
	else
		error_exit("Wrong opcode for mutex handler");
}

/* Thread errors */

static void handle_thread_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	else
		error_exit("Error Thread!");
}

/* Create Join Detach Thread */

void safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data, t_opcode opcode)
{
	if (opcode == CREATE)
		handle_thread_error(pthread_create(thread, NULL, foo, data), opcode);
	else if (opcode == JOIN)
		handle_thread_error(pthread_join(*thread, NULL), opcode);
	else if (opcode == DETACH)
		handle_thread_error(pthread_detach(*thread), opcode);
	else
		error_exit("Wrong opcode");
}
