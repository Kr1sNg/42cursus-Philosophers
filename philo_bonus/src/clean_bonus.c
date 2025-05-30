/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:20:19 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/05/30 13:14:02 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	ft_clean_all(char *message, t_simu *simu)
{
	int	i;
	int	status;

	i = 0;
	if (message)
		printf("%s\n", message);
	while (i < simu->philos[0].num_philos)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = -1;
			while (++i < simu->philos[0].num_philos)
				kill(simu->philos[i].pid, SIGTERM);
		}
		i++;
	}
	sem_close(simu->forks);
	sem_unlink("/forks");
	sem_close(simu->dead_lock);
	sem_unlink("/dead_lock");
	sem_close(simu->write_lock);
	sem_unlink("/write_lock");
	sem_close(simu->meal_lock);
	sem_unlink("/meal_lock");
	
}
