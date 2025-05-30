/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:20:19 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/05/30 16:23:28 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	main(int ac, char **av)
{
	t_simu			simu;
	t_philo			philos[PHILO_MAX];

	if (ac != 5 && ac != 6)
		return (printf(USAGE));
	if (ft_args_check(ac, av))
		return (-42);
	ft_simu_init(&simu, philos, ft_atol(av[1]));
	ft_philos_init(philos, &simu, av);
	int	i;

	i = -1;
	while (++i < ft_atol(av[1]))
	{
		philos[i].pid = fork();
		if (philos[i].pid == -1)
			return (printf("error fork()\n"), exit(EXIT_FAILURE), 1);
		if (philos[i].pid == 0)
		{
			philo_process(philos);
			exit(0);
		}
	}
	ft_clean_all(NULL, &simu);
	return (0);
}
