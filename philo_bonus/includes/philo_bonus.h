/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:21:29 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/05/31 23:48:03 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# define USAGE "Usage: number_of_philos time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philo_must_eat]\n"

# define PHILO_MAX 300

/*
** :::::::::::::::::::::::::::::::::* HEADERS *:::::::::::::::::::::::::::::: **
*/

# include <pthread.h>
# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>

/*
** :::::::::::::::::::::::::::* STRUCT DECLARATION *::::::::::::::::::::::::: **
*/

// structure of each philo
typedef struct s_philo
{
	//from av
	size_t		time_to_die;	// time_to_die
	size_t		time_to_eat;	// time_to_eat
	size_t		time_to_sleep;	// time_to_sleep
	int			num_philos;		// number_of_philos
	int			max_meals;	// number_of_times_each_must_eat (-1 if not)
	pthread_t	monitor;
	pid_t		pid[PHILO_MAX];
	int			id;

	int			meals_eaten; // number of meals he's eaten
	size_t		start_time;
	size_t		last_meal;	// time from the last meal
	bool		stop;		// this philo is dead or ate enough meals
	bool		died;
	sem_t		*write_lock;
	sem_t		*forks;

	sem_t		*stop_lock;
	sem_t		*meal_lock;
	
}	t_philo;

/*
** ::::::::::::::::::::::::::* FUNCTION PROTOTYPES *::::::::::::::::::::::::: **
*/

// times
size_t	get_time_ms(void);
void	ft_msleep(size_t ms, t_philo *philo);

// utils
long	ft_atol(char *s);
void	print_status(t_philo *philo, char *status);
void	print_error(char *message);

// init 
void	ft_philos_init(int ac, char **av, t_philo *philo);
int		get_stop(t_philo *philo);
void	set_stop(t_philo *philo, int value);

// monitor
void	*ft_monitoring(void *args);
void	ft_daily_process(t_philo *philo);

// clean
void	ft_clean_all(t_philo *philo);


int	ft_usleep(size_t ms);

void	update_last_meal(t_philo *philo);
void	increment_meals(t_philo *philo);
size_t	get_last_meal(t_philo *philo);
int		get_meals_eaten(t_philo *philo);

#endif
