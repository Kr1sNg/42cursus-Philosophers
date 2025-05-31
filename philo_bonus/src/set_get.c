/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:20:19 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/06/01 01:00:20 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	update_last_meal(t_philo *philo)
{
	sem_wait(philo->meal_lock);
	philo->last_meal = get_time_ms();
	sem_post(philo->meal_lock);
}

size_t	get_last_meal(t_philo *philo)
{
	size_t	time;

	sem_wait(philo->meal_lock);
	time = philo->last_meal;
	sem_post(philo->meal_lock);
	return (time);
}

void	increment_meals(t_philo *philo)
{
	sem_wait(philo->meal_lock);
	philo->meals_eaten++;
	sem_post(philo->meal_lock);
}

int	get_meals(t_philo *philo)
{
	int	meals;

	sem_wait(philo->meal_lock);
	meals = philo->meals_eaten;
	sem_post(philo->meal_lock);
	return (meals);
}
