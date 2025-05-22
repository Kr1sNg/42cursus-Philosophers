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
	t_simu			simu;
	t_philo			philos[PHILO_MAX];
	pthread_mutex_t forks[PHILO_MAX];

	if (ac != 5 && ac != 6)
		return (printf(USAGE));
	if (ft_simu_init(ac, av, &simu) != 0)
		return (-42);
	
	ft_simu_init(&simu, philos);
	ft_forks_init(forks, ft_atol(av[1]));
	ft_philos_init(philos, &simu, forks, av); //TODO
	//thread_create(&simu, forks); //TODO
	


	destroy_all(NULL, &simu, forks); // TODO
	return (0);
}

