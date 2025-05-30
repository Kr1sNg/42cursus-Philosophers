/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:21:29 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/05/22 12:29:32 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

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

/*
** :::::::::::::::::::::::::::* STRUCT DECLARATION *::::::::::::::::::::::::: **
*/

// structure of each philo
typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	bool			is_eating; // this philo is eating at the moment
	int				meals_eaten; // number of meals he's eaten
	size_t			last_meal;	// time from the last meal
	size_t			start_time;
	size_t			time_to_die;	// time_to_die
	size_t			time_to_eat;	// time_to_eat
	size_t			time_to_sleep;	// time_to_sleep
	int				num_philos;		// number_of_philos
	int				max_meals;	// number_of_times_each_must_eat (-1 if not)
	bool			*stop;		// this philo is dead or ate enough meals
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}	t_philo;

// structure of the simulation
typedef struct s_simu
{
	pthread_t		table;
	bool			stop;	// Flag to indicate if simulation should stop
	t_philo			*philos; // pointer to an array of t_philo structure
	pthread_mutex_t	write_lock; // mutex of writing status
	pthread_mutex_t	meal_lock; // mutex of update last meal + meals counting
	pthread_mutex_t	dead_lock; // mutex of stop flag
}	t_simu;

/*
** ::::::::::::::::::::::::::* FUNCTION PROTOTYPES *::::::::::::::::::::::::: **
*/

/* init */
int		ft_args_check(int ac, char **av);
void	ft_philos_init(t_philo *philos, t_simu *simu,
			pthread_mutex_t *forks, char **av);
void	ft_forks_init(pthread_mutex_t *forks, int num_philos);
void	ft_simu_init(t_simu *simu, t_philo *philos);

/* main */

/* monitor */
// bool	philo_dead(t_philo *philo, size_t time_to_die);
bool	is_dead(t_philo *philos);
bool	is_enough_meals(t_philo *philos);
void	*monitor(void *pointer);

/* routine */
void	ft_thinking(t_philo *philo);
void	ft_sleeping(t_philo *philo);
void	ft_dining(t_philo *philo);
void	*ft_routine(void *arg);

/* threads */
bool	stop_check_loop(t_philo *philo);
int		ft_thread_create(t_simu *simu, pthread_mutex_t *forks);

/* times */
size_t	get_time_ms(void);
int		ft_usleep(size_t ms);

/* utils */
long	ft_atol(char *s);
void	print_status(t_philo *philos, int id, char *status);

/* clean */
void	ft_clean_all(char *message, t_simu *simu, pthread_mutex_t *forks);

#endif
