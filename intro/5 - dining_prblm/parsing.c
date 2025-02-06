#include "dining.h"



void parse_input(t_table *table, char **av)
{
	table->philo_number = atol(av[1]); //TODO
	table->time_to_die = atol(av[2]) * 1e3;
	table->time_to_eat = atol(av[2]) * 1e3;
	table->time_to_sleep = atol(av[2]) * 1e3;
	if (table->time_to_die < 6e4 || table->time_to_eat < 6e4 || table->time_to_sleep <6e4)
		error_exit("Use timestamps major than 60ms"); //or not

	if (av[5])
		table->nbr_limit_meals = atol(av[5]);
	else
		table->nbr_limit_meals = -1;
}