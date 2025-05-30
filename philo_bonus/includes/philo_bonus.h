/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:21:29 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/05/30 13:25:36 by tat-nguy         ###   ########.fr       */
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
	pthread_t		monitor;
	pid_t			pid;
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
	sem_t	*left_fork;
	sem_t	*right_fork;
	sem_t	*write_lock;
	sem_t	*dead_lock;
	sem_t	*meal_lock;
	sem_t	*forks;
	
	int				fork_in_hand;
}	t_philo;

// structure of the simulation
typedef struct s_simu
{
	sem_t	*forks;
	bool			stop;	// Flag to indicate if simulation should stop
	t_philo			*philos; // pointer to an array of t_philo structure
	sem_t	*write_lock; // mutex of writing status
	sem_t	*meal_lock; // mutex of update last meal + meals counting
	sem_t	*dead_lock; // mutex of stop flag
}	t_simu;

/*
** ::::::::::::::::::::::::::* FUNCTION PROTOTYPES *::::::::::::::::::::::::: **
*/

// clean_bonus
void	ft_clean_all(char *message, t_simu *simu);

// init_bonus
int		ft_args_check(int ac, char **av);
void	ft_simu_init(t_simu *simu, t_philo *philos, int num_philos);
void	ft_philos_init(t_philo *philos, t_simu *simu, char **av);


// monitor_bonus
void	*ft_monitor(void *args);
bool	is_dead(t_philo *philos);
bool	is_enough_meals(t_philo *philos);

// routine_bonus
void	ft_thinking(t_philo *philo);
void	ft_sleeping(t_philo *philo);
void	ft_dining(t_philo *philo);
void	philo_process(t_philo *philo);

// processes
bool	stop_check_loop(t_philo *philo);
// int		ft_processes_create(t_simu *simu, int num_philos);

// times
size_t	get_time_ms(void);
int		ft_usleep(size_t ms);

// utils_bonus
long	ft_atol(char *s);
void	print_status(t_philo *philo, int id, char *status);


#endif
