/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:20:19 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/18 14:42:37 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// initializing the simulation
int ft_simu_init(int ac, char **av, t_simu *simu)
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
	simu->num_philos = ft_atol(av[1]);
	simu->time_to_die = ft_atol(av[2]);
	simu->time_to_eat = ft_atol(av[3]);
	simu->time_to_sleep = ft_atol(av[4]);
	if (ac == 6)
		simu->max_meals = ft_atol(av[5]);
	else
		simu->max_meals = -1;
	simu->stop = 0;
	simu->start_time = get_time_ms();
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
	return (NULL);
}

t_philo	ft_philo_init(t_philo *philos, t_simu *simu)
{
	int	i;

	i = 0;
	while (i < simu->num_philos)
	{
		philos[i].id = i + 1;
		
		philos[i].eating = 0;
		philos[i].meals_eaten = 0;
		//start_time !?
		philos[i].last_meal = get_time_ms();
	}

}
