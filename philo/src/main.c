/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:20:19 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/05/22 11:57:05 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int ac, char **av)
{
	t_simu			simu;
	t_philo			philos[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];

	if (ac != 5 && ac != 6)
		return (printf(USAGE));
	if (ft_args_check(ac, av))
		return (-42);
	ft_simu_init(&simu, philos);
	ft_forks_init(forks, ft_atol(av[1]));
	ft_philos_init(philos, &simu, forks, av);
	ft_thread_create(&simu, forks);
	ft_clean_all(NULL, &simu, forks);
	return (0);
}
