/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:20:19 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/05/21 19:46:51 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// check the data
int ft_args_check(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (ft_atol(av[1]) <= PHILO_MAX
			&& ft_atol(av[i]) > 0 && ft_atol(av[i]) <= INT_MAX)
			i++;
		else
			return (printf("Invalid integer arguments!\n"), -42);
	}
	// simu->num_philos = ft_atol(av[1]);
	// simu->time_to_die = ft_atol(av[2]);
	// simu->time_to_eat = ft_atol(av[3]);
	// simu->time_to_sleep = ft_atol(av[4]);
	// if (ac == 6)
	// 	simu->max_meals = ft_atol(av[5]);
	// else
	// 	simu->max_meals = -1;
	// simu->stop = 0;
	// simu->start_time = get_time_ms();
	return (0);
}

// initializing the forks mutexes
void	ft_forks_init(pthread_mutex_t *forks, int num_philos)
{
	int	i;

	i = 0;
	while (i < num_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

static void	ft_data_init(t_philo *philos, char **av)
{
	philos->time_to_die = ft_atol(av[2]);
	philos->time_to_eat = ft_atol(av[3]);
	philos->time_to_sleep = ft_atol(av[4]);
	if (av[5])
		philos->max_meals = ft_atol(av[5]);
	else
		philos->max_meals = -1;
}

void	ft_philos_init(t_philo *philos, t_simu *simu, pthread_mutex_t *forks, char **av)
{
	int	i;

	i = 0;
	while (i < ft_atol(av[1]))
	{
		philos[i].id = i + 1;
		philos[i].is_eating = false;
		philos[i].meals_eaten = 0;
		ft_data_init(&philos[i], av);
		philos[i].start_time = get_time_ms();
		philos[i].last_meal = get_time_ms();
		philos[i].write_lock = &simu->write_lock;
		philos[i].dead_lock = &simu->dead_lock;
		philos[i].meal_lock = &simu->meal_lock;
		philos[i].stop = &simu->stop; // dead_flag
		philos[i].left_fork = &forks[i];
		if (i == 0)
			philos[i].right_fork = &forks[philos[i].num_philos - 1];
		else
			philos[i].right_fork = &forks[i - 1];
		i++;
	}
}

// initializing the simulation
void	ft_simu_init(t_simu *simu, t_philo *philos)
{
	simu->stop = false;
	simu->philos = philos;
	pthread_mutex_init(&simu->write_lock, NULL);
	pthread_mutex_init(&simu->dead_lock, NULL);
	pthread_mutex_init(&simu->meal_lock, NULL);
}
