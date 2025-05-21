/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:20:19 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/05/21 19:56:07 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// check if THIS philo is dying of hunger
bool	philo_dead(t_philo *philo, int time_to_die)
{
	pthread_mutex_lock(philo->meal_lock);
	if (get_time_ms() - philo->last_meal >= time_to_die && !philo->is_eating)
		return (pthread_mutex_unlock(philo->meal_lock), true);
	pthread_mutex_unlock(philo->meal_lock);
	return (false);
}

// check in group of philos if there's a philo who died then change the stop flag
bool	is_dead(t_philo *philos)
{
	int	i;

	while (i < philos->num_philos)
	{
		if (philo_dead(&philos[i], philos->time_to_die))
		{
			print_status(&philos[i], philos[i].id, "died");
			pthread_mutex_lock(philos->dead_lock);
			*philos->stop = true;
			pthread_mutex_unlock(philos->dead_lock);
			return (true);
		}
		i++;
	}
	return (false);
}

// check in group of philos if they all have eaten enough meals then change the stop flag
bool	is_enough_meals(t_philo *philos)
{
	int	i;
	int	finish;
	
	i = 0;
	finish = 0;
	if (philos->max_meals == -1)
		return (false);
	while (i < philos->num_philos)
	{
		pthread_mutex_lock(philos[i].dead_lock);
		if (philos[i].meals_eaten >= philos->max_meals)
			finish++;
		pthread_mutex_unlock(philos[i].meal_lock);
		i++;
	}
	if (finish == philos->num_philos)
	{
		pthread_mutex_lock(philos->dead_lock);
		*philos->stop = true;
		pthread_mutex_unlock(philos->dead_lock);
		return (true);
	}
	return (false);
}

// Monitor to help check if there is a philo who died or if they all ate,
//	then we can stop simu

void	*monitor(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	while (1)
	{
		if (is_dead(philos) || is_enough_meals(philos))
			break;
	}
	return (arg);
}
