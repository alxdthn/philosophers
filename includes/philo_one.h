#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "philo_utils.h"

typedef struct s_philosopher {
	t_philo_attrs 	attrs;
	pthread_t       thread;
	pthread_mutex_t *left_hand_fork;
	pthread_mutex_t *right_hand_fork;
} t_philosopher;

typedef struct s_philo_one {
	t_program_attrs attrs;
	pthread_mutex_t fork_taking_mutex;
	pthread_mutex_t *forks;
	t_philosopher   *philosophers;
} t_philo_one;

typedef struct s_philosopher_process_argument {
	t_philo_one   *program;
	t_philosopher *philosopher;
} t_philosopher_process_argument;

bool create_philosophers(t_philo_one *program);

bool create_forks(t_philo_one *program);

void eating(t_philosopher *philosopher, t_philo_one *program);

void sleeping(t_philosopher *philosopher, t_philo_one *program);

void thinking(t_philosopher *philosopher, t_philo_one *program);

void take_forks(t_philosopher *philosopher, t_philo_one *program);

void drop_forks(t_philosopher *philosopher, t_philo_one *program);

#endif
