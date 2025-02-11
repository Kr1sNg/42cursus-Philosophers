#include "dining.h"

static void assign_forks(t_philo *philo, t_fork *fork, int philo_pos)
{
	int philo_nbr = philo->table->philo_number;

	philo->first_fork = &fork[(philo_pos + 1) % philo_nbr];
	philo->second_fork = &fork[philo_pos];
	
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &fork[philo_pos];
		philo->second_fork = &fork[(philo_pos + 1) % philo_nbr];
	}
}


static void philo_init(t_table *table)
{
	int i = -1;
	t_philo	*philo;

	while (++i < table->philo_number)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->is_enough_meals = false;
		philo->meals_counter = 0;
		philo->table = table;
		safe_mutex_handle(&philo->philo_mutex, INIT);

		assign_forks(philo, table->fork, i);
	}
}

void	data_init(t_table *table)
{
	int i = -1;

	table->end_simulation = false;
	table->all_threads_ready = false;
	table->threads_running_nbr = 0;
	table->philos = safe_malloc(sizeof(t_philo) * table->philo_number);
	safe_mutex_handle(&table->table_mutex, INIT);
	safe_mutex_handle(&table->write_mutex, INIT);
	table->fork = safe_malloc(sizeof(t_fork) * table->philo_number);
	while (++i < table->philo_number)
	{
		safe_mutex_handle(&table->fork[i].fork, INIT);
		table->fork[i].fork_id = i; // give ID to fork
	}
	philo_init(table);

}