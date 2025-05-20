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

#include "../include/philo.h"

/* 1 millisecond = 1/1000 second (tv_sec) = 1000 microsecond (tv_usec)
*/
long	get_time_ms(void)
{
	struct timeval	tv;
	
	if (gettimeofday(&tv, NULL) == -1)
		printf("gettimeofday() error\n");
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);	
}

