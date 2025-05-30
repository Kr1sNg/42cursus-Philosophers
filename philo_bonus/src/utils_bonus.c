/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:20:19 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/05/30 10:27:54 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static bool	ft_isdigits(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!((s[i] >= '0' && s[i] <= '9') || s[i] == ' ' || s[i] == '	'
				|| s[i] == '-' || s[i] == '+'))
			return (false);
		i++;
	}
	return (true);
}

long	ft_atol(char *s)
{
	int		i;
	long	nb;
	int		sign;

	if (!ft_isdigits(s))
		return (-42);
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

void	print_status(t_philo *philo, int id, char *status)
{
	sem_wait(philo->write_lock);
	if (!stop_check_loop(philo))
		printf("%ld %d %s\n", get_time_ms() - philo->start_time, id, status);
	sem_post(philo->write_lock);
}
