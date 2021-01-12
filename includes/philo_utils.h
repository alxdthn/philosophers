/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 22:57:59 by nalexand          #+#    #+#             */
/*   Updated: 2021/01/12 22:57:59 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_UTILS_H
# define PHILO_UTILS_H

# include <libc.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>

# define MONITOR_FREQUENCY_USEC 5000
# define USEC_IN_MILLIS 1000
# define UNSPECIFIED -1
# define EVEN_PHILO_THREAD_START_DELAY 42
# define FORKS_SEM_NAME "/forks"
# define FORKS_SEM_FLAGS 0644

typedef struct		s_philo_attrs {
	int				id;
	int				eat_count;
	unsigned long	last_meal;
}					t_philo_attrs;

typedef struct		s_program_attrs {
	int				n_philo;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_number;
	int				monitor_frequency;
	char			*error;
	unsigned long	time_to_die;
	unsigned long	start_time;
	t_philo_attrs	**philo_attrs;
}					t_program_attrs;

int					parse_args(int ac, char **av, t_program_attrs *result);

int					ft_numlen(unsigned x);

int					ft_strlen(const char *string);

char				*get_file_name(char *str);

int					ft_isdigit(char c);

void				ft_memcpy(void *dst, void *src, size_t size);

void				ft_putstr(const char *str);

void				ft_putstr_fd(const char *str, int fd);

int					ft_atoi(const char *str);

int					error(const char *message);

int					usage(char *file_name);

void				safe_lock_mutex(pthread_mutex_t *mutex, char **error);

void				safe_unlock_mutex(pthread_mutex_t *mutex, char **error);

void				safe_sleep_thread(unsigned long time, char **error);

void				safe_sem_wait_thread(sem_t *sem, char **error);

void				safe_sem_post_thread(sem_t *sem, char **error);

sem_t				*create_semaphore(unsigned long init_value);

bool				is_died(t_philo_attrs *philo, t_program_attrs *program);

int					monitor_process(t_program_attrs *program);

unsigned long		get_current_time_stamp(void);

unsigned long		get_time_offset(unsigned long current_time);

#endif
