/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:20:19 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/05/30 11:16:16 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

// Monitor helps to check in the table if there is a philo who died
// or if they all ate, then deciding to stop simu

void	ft_monitor(t_simu *simu)
{
	while (1)
	{
		if (is_dead(simu->philos) || is_enough_meals(simu->philos))
			break ;
	}
}

// check if THIS philo is dying of hunger
static bool	philo_dead(t_philo *philo, size_t time_to_die)
{
	sem_wait(philo->meal_lock);
	if (get_time_ms() - philo->last_meal >= time_to_die && !philo->is_eating)
		return (sem_post(philo->meal_lock), true);
	sem_post(philo->meal_lock);
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
			sem_wait(philos[0].dead_lock);
			*philos->stop = true;
			sem_post(philos[0].dead_lock);
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
		sem_wait(philos[i].meal_lock);
		if (philos[i].meals_eaten >= philos[i].max_meals)
			all++;
		sem_post(philos[i].meal_lock);
		i++;
	}
	if (all == philos[0].num_philos)
	{
		sem_wait(philos[0].dead_lock);
		*philos->stop = true;
		sem_post(philos[0].dead_lock);
		return (true);
	}
	return (false);
}
