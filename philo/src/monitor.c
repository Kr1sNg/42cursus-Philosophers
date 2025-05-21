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

// checks if the value of stop (dead_flag) changed

bool	dead_loop(t_philo *philos)
{
	pthread_mutex_lock(philos->dead_lock);
	if (*philos->dead == 1)
		return (pthread_mutex_unlock(philos->dead_lock), true);
	pthread_mutex_unlock(philos->dead_lock);
	return (false);
}

void	print_status(t_philo *philos, char *status) // need ID !?
{
	pthread_mutex_lock(philos->write_lock);
	if (!dead_loop(philos))
		printf("%ld %d %s\n", get_time_ms() - philos->start_time, philos->id, status);
	pthread_mutex_unlock(philos->write_lock);
}

// check if the philo is dead
bool	philo_dead(t_philo *philos, int	time_to_die)
{
	pthread_mutex_lock(philos->meal_lock);
	if (get_time_ms() - philos->last_meal >= time_to_die )
}

// check if there's a philo who died
bool	is_dead(t_philo *philos)
{
	int	i;

}

// Monitor to help check if there is a philo who died or if they all ate,
//	then we can stop simu

void	*monitor(void *pointer)
{
	t_philo	*philos;

	philos = (t_philo *)pointer;
	while (1)
	{
		if (is_dead(philos) || is_all_ate(philos))
			break;
	return (pointer);
	}
}
