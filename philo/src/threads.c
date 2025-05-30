/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:20:19 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/05/29 21:26:44 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
	int	i;

	if (pthread_create(&simu->table, NULL, monitor, simu->philos) != 0)
		ft_clean_all("Error of thread creation", simu, forks);
	i = 0;
	while (i < simu->philos[0].num_philos)
	{
		if (pthread_create(&simu->philos[i].thread, NULL, ft_routine,
				&simu->philos[i]) != 0)
			ft_clean_all("Error of thread creation", simu, forks);
		i++;
	}
	i = 0;
	if (pthread_join(simu->table, NULL) != 0)
		ft_clean_all("Error of thread join", simu, forks);
	while (i < simu->philos[0].num_philos)
	{
		if (pthread_join(simu->philos[i].thread, NULL) != 0)
			ft_clean_all("Error of thread join", simu, forks);
		i++;
	}
	return (0);
}
