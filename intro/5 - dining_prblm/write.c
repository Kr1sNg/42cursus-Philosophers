#include "dining.h"

// [time_ms] [philo_id] [action]

static void write_status_debug(t_status status, t_philo *philo, long elapsed)
{
	if (status == TAKE_FIRST_FORK && !simulation_finished(philo->table))
		printf(W "%-6ld" RST " %d has taken the 1st fork (fork %d)\n",
			elapsed, philo->id, philo->first_fork->fork_id);
	else if (status == TAKE_SECOND_FORK && !simulation_finished(philo->table))
		printf(W "%-6ld" RST " %d has taken the 2nd fork (fork %d)\n",
			elapsed, philo->id, philo->second_fork->fork_id);
	else if (status == EATING && !simulation_finished(philo->table))
		printf(W "%-6ld" RST " %d is eating (the %ld meals)\n",
			elapsed, philo->id, philo->meals_counter);
	else if (status == SLEEPING && !simulation_finished(philo->table))
		printf(W "%-6ld" RST " %d is eating\n", elapsed, philo->id);
	else if (status == THINKING && !simulation_finished(philo->table))
		printf(W "%-6ld" RST " %d is eating\n", elapsed, philo->id);
	else if (status == DIED)
		printf(W "%-6ld" RST " %d died\n", elapsed, philo->id);
}


void write_status(t_status status, t_philo *philo, bool debug)
{
	long elapsed;

	elapsed = gettime(MILLISECOND) - philo->table->start_simulation;
	if (philo->is_enough_meals) //thread safe
		return ;
	safe_mutex_handle(&philo->table->write_mutex, LOCK);
	if (debug)
		write_status_debug(status, philo, elapsed);
	else
	{
		if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
		&& !simulation_finished(philo->table))
			printf(W "%-6ld" RST " %d has taken the a fork\n", elapsed, philo->id);
		else if (status == EATING && !simulation_finished(philo->table))
			printf(W "%-6ld" RST " %d is eating\n", elapsed, philo->id);
		else if (status == SLEEPING && !simulation_finished(philo->table))
			printf(W "%-6ld" RST " %d is eating\n", elapsed, philo->id);
		else if (status == THINKING && !simulation_finished(philo->table))
			printf(W "%-6ld" RST " %d is eating\n", elapsed, philo->id);
		else if (status == DIED)
			printf(W "%-6ld" RST " %d died\n", elapsed, philo->id);
	}
	safe_mutex_handle(&philo->table->write_mutex, UNLOCK);
}

