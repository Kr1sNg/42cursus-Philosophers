#include "dining.h"

/* simulation of dinner */

static void thinking(t_philo *philo)
{
	write_status(THINKING, philo, DEBUG_MODE);
}


/* eat routine */
// 1- grab the forks
// 2- eat: write eat, update last meal, update meals counter, bool is_enough_meals (if needed)
// 3- release the forks

static void eat(t_philo *philo)
{
	// 1)
	safe_mutex_handle(&philo->first_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	safe_mutex_handle(&philo->second_fork->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);

	// 2)
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	philo->meals_counter++;
	write_status(EATING, philo, DEBUG_MODE);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->nbr_limit_meals > 0 && philo->meals_counter == philo->table->nbr_limit_meals)
		set_bool(&philo->philo_mutex, &philo->is_enough_meals, true);

	// 3)
	safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
	safe_mutex_handle(&philo->second_fork->fork, UNLOCK);

}




/*	- wait all philos, synchro start
**  - endless loop philo
*/
static void *dinner_simulation(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	increase_long(&philo->table->table_mutex)

	//set last meal time

	while (!simulation_finished(philo->table))
	{
		// am i full?
		if (philo->is_enough_meals)
			break;

		// eat
		eat(philo);

		//sleep => write_status & precise usleep
		write_status(SLEEPING, philo, DEBUG_MODE);
		precise_usleep(philo->table->time_to_sleep, philo->table);

		//thinking
	}
}


void dinner_start(t_table *table)
{
	int i = -1;

	if (table->nbr_limit_meals <= 0)
		return ; // back to main, clean
	else if (table->philo_number == 1)
		;//TODO
	else
	{
		while (++i < table->philo_number)
			safe_thread_handle(&table->philos[i].thread_id, dinner_simulation,
				&table->philos[i], CREATE);
	}
	// monitor
	safe_thread_handle(table->monitor, monitor_diner, table, CREATE);


	//start of simulation
	table->start_simulation = gettime(MILLISECOND);

	set_bool(&table->table_mutex, &table->all_threads_ready, true);

	i = -1;
	while (++i < table->philo_number)
		safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
	
	// if we manage to reach this line, all philos are full!

}
