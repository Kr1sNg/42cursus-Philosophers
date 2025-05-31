/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:20:19 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/06/01 00:55:55 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static int	ft_args_check(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (ft_atol(av[1]) <= PHILO_MAX
			&& ft_atol(av[i]) > 0 && ft_atol(av[i]) <= INT_MAX)
			i++;
		else
			return (printf("Invalid arguments!\n"));
	}
	return (0);
}

void	ft_philos_init(int ac, char **av, t_philo *philo)
{
	if (ft_args_check(ac, av))
		exit(EXIT_FAILURE);
	philo->num_philos = ft_atol(av[1]);
	philo->time_to_die = ft_atol(av[2]);
	philo->time_to_eat = ft_atol(av[3]);
	philo->time_to_sleep = ft_atol(av[4]);
	philo->max_meals = -1;
	if (ac == 6)
		philo->max_meals = ft_atol(av[5]);
	philo->meals_eaten = 0;
	philo->stop = 0;
	philo->died = 0;
	philo->start_time = get_time_ms();
	sem_unlink("/write_lock");
	philo->write_lock = sem_open("/write_lock", O_CREAT | O_EXCL, 0644, 1);
	sem_unlink("/stop_lock");
	philo->stop_lock = sem_open("/stop_lock", O_CREAT | O_EXCL, 0644, 1);
	sem_unlink("/meal_lock");
	philo->meal_lock = sem_open("/meal_lock", O_CREAT | O_EXCL, 0644, 1);
	sem_unlink("/forks");
	philo->forks = sem_open("/forks", O_CREAT | O_EXCL, 0644,
			philo->num_philos);
	if (!philo->write_lock || !philo->forks || !philo->stop_lock
		|| !philo->meal_lock)
		print_error("error: sem_open");
}

void	set_stop(t_philo *philo, int value)
{
	sem_wait(philo->stop_lock);
	philo->stop = value;
	sem_post(philo->stop_lock);
}

int	get_stop(t_philo *philo)
{
	int	val;

	sem_wait(philo->stop_lock);
	val = philo->stop;
	sem_post(philo->stop_lock);
	return (val);
}
