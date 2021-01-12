#include "philo_utils.h"

#ifndef PHILOSOPHERS_PHILO_THREE_H
# define PHILOSOPHERS_PHILO_THREE_H

#include <libc.h>

typedef struct s_philo_three {
	bool			is_child;
	pid_t         	*children_pid;
	sem_t           *forks_sem;
	t_philo_attrs 	*philosopher_attrs;
	t_program_attrs program_attrs;
	pthread_t     	monitor;
} t_philo_three;

sem_t *create_semaphore(unsigned long init_value);

bool create_philosophers(t_philo_three *program);

int exit_program(t_philo_three *program, int exit_code);

int eating(t_philo_three *program);

int sleeping(t_philo_three *program);

void thinking(t_philo_three *program);

int take_forks(t_philo_three *program);

int drop_forks(t_philo_three *program);

#endif //PHILOSOPHERS_PHILO_THREE_H
