/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:20:19 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/05/31 12:36:19 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	*ft_monitoring(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (!philo->stop)
	{
		usleep(100);
		
		if (get_time_ms() - philo->last_meal > philo->time_to_die)
		{
			philo->died = 1;
			sem_wait(philo->write_lock);
			printf("%ld %d %s\n", get_time_ms() - philo->start_time, philo->id, "died");
			philo->stop = 1;

			break;
		}

		if (philo->max_meals != -1 && philo->meals_eaten >= philo->max_meals)
		{
			philo->stop = 1;
			break;
		}
	}
	if (philo->died)
		exit(EXIT_FAILURE);
	else
		exit(EXIT_SUCCESS);
}

void	ft_daily_process(t_philo *philo)
{
	if (pthread_create(&philo->monitor, NULL, &ft_monitoring, philo))
		print_error("error: thread create");
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		sem_wait(philo->forks);
		print_status(philo, "has taken a fork");
		sem_wait(philo->forks);
		print_status(philo, "has taken a fork");

		print_status(philo, "is eating");
		
		ft_msleep(philo->time_to_eat, philo);

		philo->last_meal = get_time_ms();
		
		sem_post(philo->forks);
		sem_post(philo->forks);
		
		philo->meals_eaten++;

				
		print_status(philo, "is sleeping");
		
		ft_msleep(philo->time_to_sleep, philo);
		print_status(philo, "is thinking");
	}

	if (pthread_join(philo->monitor, NULL))
		print_error("error: thread join");;
}

