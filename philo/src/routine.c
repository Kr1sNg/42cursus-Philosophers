/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:20:19 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/02/05 15:37:08 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id %2 == 0)
		usleep(100);
	while (!philo->simu->stop)
	{
		print_status(philo, "is thinking");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		print_status(philo, "is eating");
		philo->last_meal = get_time_ms();
		philo->meals_eaten++;
		usleep(philo->simu->time_to_eat * 1000);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		if (philo->simu->max_meals != -1 && philo->meals_eaten >= philo->simu->max_meals)
			break;
		print_status(philo, "is sleeping");
		usleep(philo->simu->time_to_sleep * 1000);
	}
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	t_simu	*simu;
	t_philo	*philo;
	int		i;
	int		j;
	int		all_done;

	simu = (t_simu *)arg;
	while (1)
	{
		i = -1;
		while (++i < simu->num_philos)
		{
			philo = &simu->philos[i];
			if (get_time_ms() - philo->last_meal > simu->time_to_die)
			{
				pthread_mutex_lock(&simu->log_mutex);
				printf("%ld %d died\n", get_time_ms() - simu->start_time, philo->id);
				simu->stop = true;
				pthread_mutex_unlock(&simu->log_mutex);
				return (NULL);
			}
			if (simu->max_meals != -1)
			{
				all_done = 1;
				j = -1;
				while (++j < simu->num_philos)
				{
					if (simu->philos[j].meals_eaten < simu->max_meals)
						all_done = 0;
				}
				if (all_done)
				{
					simu->stop = 1;
					return (NULL);
				}
			}
		}
		usleep(1000);
	}
}
