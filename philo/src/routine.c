/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:20:19 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/05/22 15:23:48 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// routine of a philo

void	ft_thinking(t_philo *philo)
{
	print_status(philo, philo->id, "is thinking");
}

void	ft_sleeping(t_philo *philo)
{
	print_status(philo, philo->id, "is sleeping");
	ft_usleep(philo->time_to_sleep);
}

void	ft_dining(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, philo->id, "has taken a fork");
	if (philo->num_philos == 1)
	{
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, philo->id, "has taken a fork");
	philo->is_eating = true;
	print_status(philo, philo->id, "is eating");
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	philo->is_eating = false;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!stop_check_loop(philo))
	{
		ft_dining(philo);
		ft_sleeping(philo);
		ft_thinking(philo);
	}
	return (arg);
}
