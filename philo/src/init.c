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

int ft_simu_init(int ac, char **av, t_simu *simu)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (ft_atol(av[i]) > 0 && ft_atol(av[i]) <= INT_MAX)
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

t_philo	ft_philo_init(t_simu *simu)
{
	t_philo philos;

	simu->forks = malloc(sizeof(pthread_mutex_t) * simu->num_philos);
	
}