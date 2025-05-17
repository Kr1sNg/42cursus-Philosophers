/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:21:29 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/18 15:06:22 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#define USAGE "Usage: number_of_philos time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philo_must_eat]\n"

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

/*
** :::::::::::::::::::::::::::* STRUCT DECLARATION *::::::::::::::::::::::::: **
*/

struct s_philo;

// structure of the simulation
typedef struct s_simu
{
	int		num_philos;		// number_of_philos
	int 	time_to_die;	// time_to_die
	int 	time_to_eat;	// time_to_eat
	int 	time_to_sleep;	// time_to_sleep
	int 	max_meals;		// number_of_times_each_philo_must_eat (-1 if not specified)
	bool	stop;			// Flag to indicate if simulation should stop (0 = continue, 1 = stop)
	pthread_mutex_t	*forks;
	struct s_philo	*philos; // pointer to an array of t_philo structure
	pthread_mutex_t	log_mutex; // protecting the printing process
	// pthread_mutex_t	stop_mutex; // protect the stop flag
	long	start_time;
}	t_simu;

// structure of each philo
typedef struct s_philo
{
	int		id;
	t_simu	*simu;
	pthread_t	thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long	last_meal;
	int		meals_eaten;
}	t_philo;

/*
** ::::::::::::::::::::::::::* FUNCTION PROTOTYPES *::::::::::::::::::::::::: **
*/

/* utils */
long	ft_atol(char *s);
long	get_time_ms(void);
void	print_status(t_philo *philo, char *status);

/* init */
int 	ft_simu_init(int ac, char **av, t_simu *simu);

/* main */

#endif
