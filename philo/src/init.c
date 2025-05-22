/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:20:19 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/05/22 11:56:30 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// check the data
int	ft_args_check(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (ft_atol(av[1]) <= PHILO_MAX
			&& ft_atol(av[i]) > 0 && ft_atol(av[i]) <= INT_MAX)
			i++;
		else
			return (printf("Invalid arguments!\n"), -42);
	}
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

static void	ft_data_init(t_philo *philo, char **av)
{
	philo->num_philos = ft_atol(av[1]);
	philo->time_to_die = ft_atol(av[2]);
	philo->time_to_eat = ft_atol(av[3]);
	philo->time_to_sleep = ft_atol(av[4]);
	if (av[5] != NULL)
		philo->max_meals = ft_atol(av[5]);
	else
		philo->max_meals = -1;
}

void	ft_philos_init(t_philo *philos, t_simu *simu,
			pthread_mutex_t *forks, char **av)
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
		philos[i].stop = &simu->stop;
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
