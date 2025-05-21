/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:20:19 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/05/21 19:12:14 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_clean_all(char *message, t_simu *simu, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	if (message)
		printf("%s\n", message);
	pthread_mutex_destroy(&simu->write_lock);
	pthread_mutex_destroy(&simu->meal_lock);
	pthread_mutex_destroy(&simu->dead_lock);
	while (i < simu->philos->num_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}
