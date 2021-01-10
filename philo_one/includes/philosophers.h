#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <libc.h>
# include <unistd.h>

# define THINKING 0
# define EATING 1
# define SLIPPING 2
# define MICRO_SEC_IN_MILLIS 1000

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
	int number_of_philosophers;
	int time_to_eat;
	int time_to_sleep;
	int time_to_die;
	int number_of_times_each_philosopher_must_eat;
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

long get_time_offset(t_program *program);

void monitor_process(t_program *program);

void print_number(unsigned long time);

void print_status(long time, int philosopher_id, char *status);

#endif
