#ifndef PHILOSOPHERS_PHILO_TWO_H
# define PHILOSOPHERS_PHILO_TWO_H

# include "philo_utils.h"

# define FORKS_SEMAPHORE_NAME "/forks2"

typedef struct s_philosopher {
	t_philo_attrs attrs;
	pthread_t     thread;
} t_philosopher;

typedef struct s_philo_two {
	sem_t           *forks_sem;
	t_program_attrs attrs;
	t_philosopher   *philosophers;
} t_philo_two;

typedef struct s_philosopher_process_argument {
	t_philo_two   *program;
	t_philosopher *philosopher;
} t_philosopher_process_argument;

sem_t *create_semaphore(unsigned long init_value);

bool create_philosophers(t_philo_two *program);

int exit_program(sem_t * sem, int exit_code);

void eating(t_philosopher *philosopher, t_philo_two *program);

void sleeping(t_philosopher *philosopher, t_philo_two *program);

void thinking(t_philosopher *philosopher, t_philo_two *program);

void take_forks(t_philosopher *philosopher, t_philo_two *program);

void drop_forks(t_philo_two *program);

#endif //PHILOSOPHERS_PHILO_TWO_H
