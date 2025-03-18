/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:20:19 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/02/05 15:37:08 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"


int	main(int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (printf("Usage: number_of_philos time_to_die time_to_eat \
			time_to_sleep [number_of_times_each_philo_must_eat]\n"));
	
}

