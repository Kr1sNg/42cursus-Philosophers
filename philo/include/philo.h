/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:21:29 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/05/21 19:46:55 by tat-nguy         ###   ########.fr       */
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
	pthread_t	thread;
	int			id;
	bool		is_eating; // this philo is eating at the moment
	int			meals_eaten; // number of meals he's eaten
	long		last_meal;	// time from the last meal

	long	start_time;
	
	int 	time_to_die;	// time_to_die
	int 	time_to_eat;	// time_to_eat
	int 	time_to_sleep;	// time_to_sleep
	int		num_philos;		// number_of_philos
	int 	max_meals;		// number_of_times_each_philo_must_eat (-1 if not specified)
	
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
	bool	stop;	// dead_flag	// Flag to indicate if simulation should stop (0 = continue, 1 = stop)
	t_philo			*philos; // pointer to an array of t_philo structure
	
	//pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock; //log_mutex; // protecting the printing process
	// pthread_mutex_t	stop_mutex; // protect the stop flag
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	dead_lock;
	
}	t_simu;


/*
** ::::::::::::::::::::::::::* FUNCTION PROTOTYPES *::::::::::::::::::::::::: **
*/



/* init */
int		ft_args_check(int ac, char **av);
void	ft_philos_init(t_philo *philos, t_simu *simu, pthread_mutex_t *forks, char **av);
void	ft_forks_init(pthread_mutex_t *forks, int num_philos);
void 	ft_simu_init(t_simu *simu, t_philo *philos);

/* main */

/* monitor */
bool	philo_dead(t_philo *philo, int time_to_die);
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
long	get_time_ms(void);
int		ft_usleep(int ms);

/* utils */
long	ft_atol(char *s);
void	print_status(t_philo *philos, int id, char *status);

/* clean */
void	ft_clean_all(char *message, t_simu *simu, pthread_mutex_t *forks);

#endif
