#include "example.h"

long get_time_ms(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void print_status(t_philo *philo, char *status) {
    pthread_mutex_lock(&philo->sim->log_mutex);
    pthread_mutex_lock(&philo->sim->stop_mutex);
    int stop = philo->sim->stop;
    pthread_mutex_unlock(&philo->sim->stop_mutex);
    if (!stop || strcmp(status, "died") == 0) {
        printf("%ld %d %s\n", get_time_ms() - philo->sim->start_time, philo->id, status);
    }
    pthread_mutex_unlock(&philo->sim->log_mutex);
}

void *philo_routine(void *arg) {
    t_philo *philo = (t_philo *)arg;
    while (1) {
        pthread_mutex_lock(&philo->sim->stop_mutex);
        if (philo->sim->stop) {
            pthread_mutex_unlock(&philo->sim->stop_mutex);
            break;
        }
        pthread_mutex_unlock(&philo->sim->stop_mutex);
        
        // Alternate fork order based on philosopher ID to prevent deadlock
        if (philo->id % 2 == 0) {
            pthread_mutex_lock(philo->left_fork);
            print_status(philo, "has taken a fork");
            pthread_mutex_lock(philo->right_fork);
            print_status(philo, "has taken a fork");
        } else {
            pthread_mutex_lock(philo->right_fork);
            print_status(philo, "has taken a fork");
            pthread_mutex_lock(philo->left_fork);
            print_status(philo, "has taken a fork");
        }
        
        print_status(philo, "is eating");
        pthread_mutex_lock(&philo->meal_mutex);
        philo->last_meal = get_time_ms();
        philo->meals_eaten++;
        pthread_mutex_unlock(&philo->meal_mutex);
        usleep(philo->sim->time_to_eat * 1000);
        
        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);

        pthread_mutex_lock(&philo->meal_mutex);
        int meals = philo->meals_eaten;
        pthread_mutex_unlock(&philo->meal_mutex);
        if (philo->sim->max_meals != -1 && meals >= philo->sim->max_meals) {
            break;
        }
		print_status(philo, "is thinking");
		
        print_status(philo, "is sleeping");
        usleep(philo->sim->time_to_sleep * 1000);
    }
    return NULL;
}

void *monitor_routine(void *arg) {
    t_sim *sim = (t_sim *)arg;
    while (1) {
        int someone_died = 0;
        for (int i = 0; i < sim->num_philos; i++) {
            t_philo *philo = &sim->philos[i];
            pthread_mutex_lock(&philo->meal_mutex);
            long last_meal = philo->last_meal;
            pthread_mutex_unlock(&philo->meal_mutex);
            if ((get_time_ms() - last_meal) > sim->time_to_die) {
                pthread_mutex_lock(&sim->log_mutex);
                printf("%ld %d died\n", get_time_ms() - sim->start_time, philo->id);
                pthread_mutex_lock(&sim->stop_mutex);
                sim->stop = 1;
                pthread_mutex_unlock(&sim->stop_mutex);
                pthread_mutex_unlock(&sim->log_mutex);
                someone_died = 1;
                break;
            }
        }
        if (someone_died) break;

        if (sim->max_meals != -1) {
            int all_done = 1;
            for (int j = 0; j < sim->num_philos; j++) {
                t_philo *philo = &sim->philos[j];
                pthread_mutex_lock(&philo->meal_mutex);
                int meals = philo->meals_eaten;
                pthread_mutex_unlock(&philo->meal_mutex);
                if (meals < sim->max_meals) {
                    all_done = 0;
                    break;
                }
            }
            if (all_done) {
                pthread_mutex_lock(&sim->stop_mutex);
                sim->stop = 1;
                pthread_mutex_unlock(&sim->stop_mutex);
                break;
            }
        }
        usleep(1000); // Check every 1ms to reduce CPU load
    }
    return NULL;
}

int main(int argc, char **argv) {
    if (argc < 5 || argc > 6) {
        printf("Usage: %s num_philos time_to_die time_to_eat time_to_sleep [max_meals]\n", argv[0]);
        return 1;
    }
    t_sim sim = {0};
    sim.num_philos = atoi(argv[1]);
    sim.time_to_die = atoi(argv[2]);
    sim.time_to_eat = atoi(argv[3]);
    sim.time_to_sleep = atoi(argv[4]);
    sim.max_meals = (argc == 6) ? atoi(argv[5]) : -1;
    sim.start_time = get_time_ms();
    sim.stop = 0;

    sim.forks = malloc(sizeof(pthread_mutex_t) * sim.num_philos);
    t_philo *philos = malloc(sizeof(t_philo) * sim.num_philos);
    pthread_mutex_init(&sim.log_mutex, NULL);
    pthread_mutex_init(&sim.stop_mutex, NULL);
    for (int i = 0; i < sim.num_philos; i++) {
        pthread_mutex_init(&sim.forks[i], NULL);
        pthread_mutex_init(&philos[i].meal_mutex, NULL);
    }
    for (int i = 0; i < sim.num_philos; i++) {
        philos[i].id = i + 1;
        philos[i].sim = &sim;
        philos[i].left_fork = &sim.forks[i];
        philos[i].right_fork = &sim.forks[(i + 1) % sim.num_philos];
        philos[i].last_meal = sim.start_time;
        philos[i].meals_eaten = 0;
    }
    sim.philos = philos;

    pthread_t monitor;
    for (int i = 0; i < sim.num_philos; i++) {
        if (pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]) != 0) {
            fprintf(stderr, "Error creating thread\n");
            return 1;
        }
    }
    if (pthread_create(&monitor, NULL, monitor_routine, &sim) != 0) {
        fprintf(stderr, "Error creating monitor thread\n");
        return 1;
    }

    for (int i = 0; i < sim.num_philos; i++)
        pthread_join(philos[i].thread, NULL);
    pthread_join(monitor, NULL);

    for (int i = 0; i < sim.num_philos; i++) {
        pthread_mutex_destroy(&sim.forks[i]);
        pthread_mutex_destroy(&philos[i].meal_mutex);
    }
    pthread_mutex_destroy(&sim.log_mutex);
    pthread_mutex_destroy(&sim.stop_mutex);
    free(sim.forks);
    free(philos);
    return 0;
}
