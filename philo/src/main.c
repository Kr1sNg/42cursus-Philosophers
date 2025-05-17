/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:20:19 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/18 15:07:09 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int ac, char **av)
{
	t_simu	simu;
	t_philo	*philos;

	if (ac != 5 && ac != 6)
		return (printf(USAGE));
	if (ft_simu_init(ac, av, &simu) != 0)
		return (-42);

	simu.forks = malloc(sizeof(pthread_mutex_t) * simu.num_philos);
	philos = malloc(sizeof(t_philo) * simu.num_philos);
	pthread_mutex_init(&simu.log_mutex, NULL);
	while 
	
	
}

