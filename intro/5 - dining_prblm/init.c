#include "dining.h"

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
		assign_forks(philo, table->fork, i);
	}
}

void	data_init(t_table *table)
{
	int i = -1;

	table->end_simulation = false;
	table->philos = safe_malloc(sizeof(t_philo) * table->philo_number);
	table->fork = safe_malloc(sizeof(t_fork) * table->philo_number);
	while (++i < table->philo_number)
	{
		safe_mutex_handle(&table->fork[i].fork, INIT);
		table->fork[i].fork_id = i; // give ID to fork
	}
	philo_init(table);

}