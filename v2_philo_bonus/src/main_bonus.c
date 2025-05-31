/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:20:19 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/05/31 11:45:16 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"


int	main(int ac, char **av)
{
	t_philo			philo;
	int				i;

	if (ac != 5 && ac != 6)
		return (printf(USAGE));
		
	ft_philos_init(ac, av, &philo); //TODO
		
	philo.start_time = get_time_ms();
	i = -1;
	while (++i < philo.num_philos)
	{
		philo.pid[i] = fork();
		if (philo.pid[i] == -1)
			print_error("error: fork");
		if (philo.pid[i] == 0)
		{
			philo.id = i + 1;
			philo.last_meal = get_time_ms();
			ft_daily_process(&philo); //TODO
		}
	}
	ft_clean_all(&philo); //TODO
	return (0);
}
