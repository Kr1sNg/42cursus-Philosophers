/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:20:19 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/05/31 12:26:15 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	ft_clean_all(t_philo *philo)
{
	int	i;
	int	status;

	i = 0;
	while (i < philo->num_philos)
	{
		waitpid(-1, &status, 0);
		if ((WIFEXITED(status) && WEXITSTATUS(status) != 0) || WIFSIGNALED(status))
		{
			i = -1;
			while (++i < philo->num_philos)
				kill(philo->pid[i], SIGKILL);
			break;
		}
		i++;
	}
	sem_close(philo->write_lock);
	sem_unlink("/write_lock");
	
	// sem_close(philo->meal_lock);
	// sem_unlink("/meal_lock");
	
	sem_close(philo->forks);
	sem_unlink("/forks");

	// free(philo->pid);
}
