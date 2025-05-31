/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:20:19 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/05/31 08:51:42 by tat-nguy         ###   ########.fr       */
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
	philo->fork_in_hand++;
	if (philo->num_philos == 1)
	{
		ft_usleep(philo->time_to_die);
		sem_post(philo->forks);
		return ;
	}
	if (philo->fork_in_hand < 2)
	{
		sem_wait(philo->forks);
		print_status(philo, philo->id, "has taken a fork");
		philo->fork_in_hand++;
		philo->is_eating = true;
		print_status(philo, philo->id, "is eating");
		sem_wait(philo->meal_lock);
		philo->last_meal = get_time_ms();
		philo->meals_eaten++;
		sem_post(philo->meal_lock);
		ft_usleep(philo->time_to_eat);
		philo->is_eating = false;
		sem_post(philo->forks);
	}
	else
	{
		printf("fork in hand: %i\n", philo->fork_in_hand);
		sleep(5);
		philo->fork_in_hand--;
	}
	sem_post(philo->forks);
	philo->fork_in_hand--;
}

void	philo_process(t_philo *philo)
{
	if (pthread_create(&philo->monitor, NULL, &ft_monitor, philo))
	{
		printf("error: thread creation\n");
		exit(1);
	}	
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!stop_check_loop(philo))
	{
		ft_dining(philo);
		ft_sleeping(philo);
		ft_thinking(philo);
	}
	if (pthread_join(philo->monitor, NULL))
	{
		printf("error: thread join\n");
		exit(1);
	}
}
