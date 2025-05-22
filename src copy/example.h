#ifndef PHILO_H
#define PHILO_H
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>

typedef struct s_sim {
    int num_philos;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int max_meals;
    int stop;
    pthread_mutex_t *forks;
    pthread_mutex_t log_mutex;
    pthread_mutex_t stop_mutex;
    long start_time;
    struct s_philo *philos;
} t_sim;

typedef struct s_philo {
    int id;
    t_sim *sim;
    pthread_t thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    long last_meal;
    int meals_eaten;
    pthread_mutex_t meal_mutex; // Added to protect meal data
} t_philo;

long get_time_ms(void);
void *philo_routine(void *arg);
void *monitor_routine(void *arg);
void print_status(t_philo *philo, char *status);
#endif
