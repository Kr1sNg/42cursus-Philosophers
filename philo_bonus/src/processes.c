/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:20:19 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/05/30 10:44:33 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

// checks if the value of is_dead flag changed
bool	stop_check_loop(t_philo *philo)
{
	sem_wait(philo->dead_lock);
	if (*philo->stop == true)
		return (sem_post(philo->dead_lock), true);
	sem_post(philo->dead_lock);
	return (false);
}

// create the processes
int	ft_processes_create(t_simu *simu, int num_philos)
{
	int	i;

	i = 0;
	while (i < num_philos)
	{
		simu->philos[i].pid = fork();
		if (simu->philos[i].pid == -1)
			return (printf("error fork()\n"), exit(EXIT_FAILURE), 1);
		if (simu->philos[i].pid == 0)
			philo_process(simu, simu->philos[i].id);
		i++;
	}
	return (0);
}
