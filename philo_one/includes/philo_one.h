#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "philo_parse.h"

# define THINKING 0
# define EATING 1
# define SLIPPING 2

# define MONITOR_FREQUENCY (1 * 1000 * 9)

typedef struct s_philosopher {
	int             id;
	int             status;
	long            last_eating;
	char            *error;
	pthread_t       thread;
	pthread_mutex_t *left_hand_fork;
	pthread_mutex_t *right_hand_fork;
} t_philosopher;

typedef struct s_program {

	int monitor_frequency;
	long start_time;

	t_parse_result	attrs;

	pthread_mutex_t fork_taking_mutex;
	pthread_mutex_t *forks;

	t_philosopher *philosophers;
} t_program;

typedef struct s_philosopher_process_argument {
	t_program     *program;
	t_philosopher *philosopher;
} t_philosopher_process_argument;

void monitor_process(t_program *program);

#endif
