/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:20:19 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/18 14:42:37 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	ft_atol(char *s)
{
	int		i;
	long	nb;
	int		sign;
	
	i = 0;
	nb = 0;
	sign = 1;
	while (s[i] == ' ' || s[i] == '	')
		i++;
	if (s[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (s[i] == '+')
		i++;
	while (s[i] >= '0' && s[i] <= '9')
	{
		nb = nb * 10 + (s[i] - '0');
		i++;
	}
	return (nb * sign);
}

int ft_philo_init(int ac, char **av, t_philo *philos)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (ft_atol(av[i]) > 0 && ft_atol(av[i]) <= INT_MAX)
			i++;
		else
			return (printf("Invalid integer arguments!\n"), -42);
	}
	philos->philos = ft_atol(av[1]);
	philos->time_to_die = ft_atol(av[2]);
	philos->time_to_eat = ft_atol(av[3]);
	philos->time_to_sleep = ft_atol(av[4]);
	if (av[5])
		philos->times_must_eat = ft_atol(av[5]);
	return (0);
}

