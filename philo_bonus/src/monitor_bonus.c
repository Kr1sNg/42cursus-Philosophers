/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:20:19 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/05/31 23:54:56 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	*ft_monitoring(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (!get_stop(philo))
	{
		usleep(100);
		if (get_time_ms() - get_last_meal(philo) > philo->time_to_die)
		{
			philo->died = 1;
			sem_wait(philo->write_lock);
			printf("%ld %d %s\n", get_time_ms() - philo->start_time, philo->id,
				"died");
			set_stop(philo, 1);
			// philo->stop = 1;
			break ;
		}

		if (philo->max_meals != -1 && (get_meals_eaten(philo) >= philo->max_meals))
		{
			set_stop(philo, 1);
			// philo->stop = 1;
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
		ft_usleep(1);
	while (1)
	{
		sem_wait(philo->forks);
		print_status(philo, "has taken a fork");
		sem_wait(philo->forks);
		print_status(philo, "has taken a fork");

		print_status(philo, "is eating");
		
		ft_msleep(philo->time_to_eat, philo);

		
		sem_post(philo->forks);
		sem_post(philo->forks);
		
		update_last_meal(philo);
		increment_meals(philo);
		// philo->last_meal = get_time_ms();
		
		// philo->meals_eaten++;

				
		print_status(philo, "is sleeping");
		
		ft_msleep(philo->time_to_sleep, philo);
		print_status(philo, "is thinking");
	}

	if (pthread_join(philo->monitor, NULL))
		print_error("error: thread join");;
}

