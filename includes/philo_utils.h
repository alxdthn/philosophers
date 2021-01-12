#ifndef PHILOSOPHERS_UTILS_H
# define PHILOSOPHERS_UTILS_H

# include <libc.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>

# define MONITOR_FREQUENCY_USEC 5000
# define MICRO_SEC_IN_MILLIS 1000
# define UNSPECIFIED -1
# define EVEN_PHILO_THREAD_START_DELAY 42
# define FORKS_SEMAPHORE_NAME "/forks"
# define FORKS_SEMAPHORE_FLAGS 0644

typedef struct s_philo_attrs {
	int           id;
	int           eat_count;
	unsigned long last_meal;
} t_philo_attrs;

typedef struct s_program_attrs {
	int           number_of_philosophers;
	int           time_to_eat;
	int           time_to_sleep;
	int           number_of_times_each_philosopher_must_eat;
	int           monitor_frequency;
	char          *error;
	unsigned long time_to_die;
	unsigned long start_time;
	t_philo_attrs **philo_attrs;
} t_program_attrs;

int parse_args(int ac, char **av, t_program_attrs *result);

int ft_numlen(unsigned x);

int ft_strlen(const char *string);

int ft_isdigit(char c);

void ft_memcpy(void *dst, void *src, size_t size);

void ft_putstr_fd(const char *str, int fd);

int ft_atoi(const char *str);

int error(const char *message);

int usage();

void safe_lock_thread_mutex(pthread_mutex_t *mutex, char **error);

void safe_unlock_thread_mutex(pthread_mutex_t *mutex, char **error);

void safe_sleep_thread(unsigned long time, char **error);

void safe_sem_wait_thread(sem_t *sem, char **error);

void safe_sem_post_thread(sem_t *sem, char **error);

sem_t *create_semaphore(unsigned long init_value);

bool check_is_died(t_philo_attrs *philo_attrs, t_program_attrs *program_attrs);

int monitor_process(t_program_attrs *program);

unsigned long get_current_time_stamp();

unsigned long get_time_offset(unsigned long current_time);

#endif
