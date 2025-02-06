#ifndef DINING_H
# define DINING_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>
/*
./philo 5 800 200 200 (5) */

#ifndef COLORS_H
# define COLORS_H

/* ANSI escape sequences for bold text colors
** Usage:
** Use the macros inside printf to print colored text. For example:
** printf(R "This is bold red text" RST);
** printf(G "Success!" RST);
** Always end with RST to reset text formatting.
*/
# define RST	"\033[0m" /* Reset */
# define BL		"\033[1;30m" /* Bold Black */
# define R		"\033[1;31m" /* Bold Red */
# define G		"\033[1;32m" /* Bold Green */
# define Y		"\033[1;33m" /* Bold Yellow */
# define B		"\033[1;34m" /* Bold Blue */
# define M		"\033[1;35m" /* Bold Magenta */
# define C		"\033[1;36m" /* Bold Cyan */
# define W		"\033[1;37m" /* Bold White */
#endif // COLORS_H



/*structure*/

typedef pthread_mutex_t t_mtx;
typedef struct s_table t_table;

// Fork
typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}	t_fork;


// Philo

typedef struct s_philo
{
	int 		id;
	long		meals_counter;
	bool		is_enough_meals;
	long		last_meal_time; //the time passed from last meal
	t_fork		*left_fork;
	t_fork		*right_fork;
	pthread_t	thread_id;
	t_table		*table;
}	t_philo;

// Table

struct s_table
{
	long	philo_number;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	nbr_limit_meals; // flag if -1 like there's no arg
	long	start_simulation;
	bool	end_simulation;
	t_fork	*fork;
	t_philo	*philos;
};

/* Utils */
void	error_exit(const char *error);

/* Parsing */
void parse_input(t_table *table, char **av);


#endif