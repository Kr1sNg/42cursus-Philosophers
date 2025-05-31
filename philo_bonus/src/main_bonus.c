/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:20:19 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/05/31 20:20:30 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	main(int ac, char **av)
{
	t_philo	philo;
	int		i;

	if (ac != 5 && ac != 6)
		return (printf(USAGE));
	ft_philos_init(ac, av, &philo);
	i = -1;
	while (++i < philo.num_philos)
	{
		philo.pid[i] = fork();
		if (philo.pid[i] == -1)
			print_error("error: fork");
		if (philo.pid[i] == 0)
		{
			philo.id = i + 1;
			ft_daily_process(&philo);
		}
	}
	ft_clean_all(&philo);
	return (0);
}
