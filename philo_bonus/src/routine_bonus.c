/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:20:19 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/05/30 11:16:36 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

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
	sem_wait(philo->forks);
	print_status(philo, philo->id, "has taken a fork");
	if (philo->num_philos == 1)
	{
		ft_usleep(philo->time_to_die);
		sem_post(philo->forks);
		return ;
	}
	sem_wait(philo->forks);
	print_status(philo, philo->id, "has taken a fork");
	philo->is_eating = true;
	print_status(philo, philo->id, "is eating");
	sem_wait(philo->meal_lock);
	philo->last_meal = get_time_ms();
	philo->meals_eaten++;
	sem_post(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	philo->is_eating = false;
	sem_post(philo->forks);
	sem_post(philo->forks);
}

void	philo_process(t_simu *simu, int	id)
{
	t_philo	*philo;

	philo = &simu->philos[id];
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!stop_check_loop(philo))
	{
		ft_dining(philo);
		ft_sleeping(philo);
		ft_thinking(philo);
	}
}
