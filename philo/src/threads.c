/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:20:19 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/05/21 19:56:35 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// checks if the value of is_dead flag changed
bool	stop_check_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->stop == true)
		return (pthread_mutex_unlock(philo->dead_lock), true);
	pthread_mutex_unlock(philo->dead_lock);
	return (false);
}

// create the threads
int	ft_thread_create(t_simu *simu, pthread_mutex_t *forks)
{
	pthread_t	table;
	int			i;

	if (pthread_create(&table, NULL, &monitor, simu->philos))
		ft_clean_all("Error of thread creation", simu, forks);
	i = 0;
	while (i < simu->philos->num_philos)
	{
		if (pthread_create(&simu->philos[i].thread, NULL, &ft_routine, &simu->philos[i]))
			ft_clean_all("Error of thread creation", simu, forks);
		i++;
	}
	i = 0;
	if (pthread_join(table, NULL))
		ft_clean_all("Error of thread join", simu, forks);
	while (i < simu->philos->num_philos)
	{
		if (pthread_join(simu->philos[i].thread, NULL))
			ft_clean_all("Error of thread join", simu, forks);
		i++;
	}
	return (0);
}
