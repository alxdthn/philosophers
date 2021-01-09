#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <libc.h>

# define THINKING 0
# define EATING 1
# define SLIPPING 2

typedef struct s_philosopher {
	int             id;
	int             status;
	long            last_eating;
	char            *error;
	pthread_t       thread;
	pthread_mutex_t self_mutex;
	pthread_mutex_t *left_hand_fork;
	pthread_mutex_t *right_hand_fork;
} t_philosopher;

typedef struct s_program {
	int is_running;
	int number_of_philosophers;
	int time_to_eat;
	int time_to_sleep;
	int time_to_die;
	int monitor_frequency;

	long start_time;

	pthread_mutex_t fork_taking_mutex;
	pthread_mutex_t *forks;

	t_philosopher *philosophers;
} t_program;

typedef struct s_philosopher_process_argument {
	t_program     *program;
	t_philosopher *philosopher;
} t_philosopher_process_argument;

long get_current_time_stamp();

long get_time_offset();

void *monitor_process(void *arg);

#endif
