/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   times.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:20:19 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/05/31 23:34:20 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

/* 1 millisecond = 1/1000 second (tv_sec) = 1000 microsecond (tv_usec)
*/
size_t	get_time_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		printf("error: gettimeofday()\n");
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	ft_usleep(size_t ms)
{
	size_t	start;

	start = get_time_ms();
	while (get_time_ms() - start < ms)
		usleep(500);
	return (0);
}

void ft_msleep(size_t ms, t_philo *philo)
{
	size_t	start;
	
	start = get_time_ms();
	while (!get_stop(philo))
	{	
		if (get_time_ms() - start >= ms)
			break;
		usleep(500);
	}
}
