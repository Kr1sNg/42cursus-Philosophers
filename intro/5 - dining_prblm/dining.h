// 1:39:13 dinner.c


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

/* write */
# define DEBUG_MODE 1

/* Enum */

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}			t_opcode;


/* Enum for get time */
typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}			t_time_code;


/* Enum for philo states */
typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}		t_status;



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
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;
	t_mtx		philo_mutex;
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
	bool	all_threads_ready;
	long	threads_running_nbr;
	pthread_t monitor;
	t_mtx	table_mutex;
	t_mtx	write_mutex;
	t_fork	*fork;
	t_philo	*philos;
};

/* Utils */
void	error_exit(const char *error);
long gettime(t_time_code time_code);
void	precise_usleep(long usec, t_table *table);

/* Parsing */
void parse_input(t_table *table, char **av);

/* Safe */
void *safe_malloc(size_t bytes);
void safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
void safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data, t_opcode opcode);


/* Init */
void	data_init(t_table *table);

/* getter - setter */
void set_bool(t_mtx *mutex, bool *dest, bool value);
bool get_bool(t_mtx *mutex, bool *value);
void set_long(t_mtx *mutex, long *dest, long value);
long get_long(t_mtx *mutex, long *value);
bool simulation_finished(t_table *table);

/* syncho utils */
void wait_all_threads(t_table *table);

/* write */
void write_status(t_status status, t_philo *philo, bool debug);

/* dinner */
void dinner_start(t_table *table);


#endif