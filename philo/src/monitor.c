/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:20:19 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/05/29 21:26:44 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// Monitor helps to check in the table if there is a philo who died
// or if they all ate, then deciding to stop simu

void	*monitor(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	while (1)
	{
		if (is_dead(philos) || is_enough_meals(philos))
			break ;
	}
	return (arg);
}

// check if THIS philo is dying of hunger
static bool	philo_dead(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(philo->meal_lock);
	if (get_time_ms() - philo->last_meal >= time_to_die && !philo->is_eating)
		return (pthread_mutex_unlock(philo->meal_lock), true);
	pthread_mutex_unlock(philo->meal_lock);
	return (false);
}

// check in table if there's a philo who died then change the stop flag
bool	is_dead(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].num_philos)
	{
		if (philo_dead(&philos[i], philos[i].time_to_die))
		{
			print_status(&philos[i], philos[i].id, "died");
			pthread_mutex_lock(philos[0].dead_lock);
			*philos->stop = true;
			pthread_mutex_unlock(philos[0].dead_lock);
			return (true);
		}
		i++;
	}
	return (false);
}

// check in table if they all have eaten enough meals then change the stop flag
bool	is_enough_meals(t_philo *philos)
{
	int	i;
	int	all;

	i = 0;
	all = 0;
	if (philos[0].max_meals == -1)
		return (false);
	while (i < philos[0].num_philos)
	{
		pthread_mutex_lock(philos[i].meal_lock);
		if (philos[i].meals_eaten >= philos[i].max_meals)
			all++;
		pthread_mutex_unlock(philos[i].meal_lock);
		i++;
	}
	if (all == philos[0].num_philos)
	{
		pthread_mutex_lock(philos[0].dead_lock);
		*philos->stop = true;
		pthread_mutex_unlock(philos[0].dead_lock);
		return (true);
	}
	return (false);
}
