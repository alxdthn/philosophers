/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 22:57:59 by nalexand          #+#    #+#             */
/*   Updated: 2021/01/18 22:36:34 by nalexand         ###   ########.fr       */
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

# define USEC_IN_MILLIS 1000
# define MONITOR_FREQUENCY_USEC 1000
# define UNSPECIFIED -1
# define MAGIC_CONSTANT 50
# define FORKS_SEM_NAME "/forks"
# define FORKS_SEM_FLAGS 0644
# define EAT " is eating\n"
# define SLEEP " is sleeping\n"
# define THINK " is thinking\n"
# define FORK " has taken a fork\n"
# define DIE " died\n"
# define TIME 0
# define ID 1
# define STATUS 2
# define LOCK_PRINT 1
# define DONT_LOCK 0
# define PHILO_START_OFFSET 42

typedef struct		s_print_lock {
	void			(* lock)(void);
	void			(* unlock)(void);
}					t_print_lock;

typedef struct		s_philo_attrs {
	int				id;
	int				eat_count;
	unsigned long	last_meal;
}					t_philo_attrs;

typedef struct		s_attrs {
	bool			is_ready;
	int				n_philo;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_number;
	int				ready_philo_number;
	char			*error;
	unsigned long	time_to_die;
	unsigned long	start_time;
	t_philo_attrs	**philo_attrs;
	t_print_lock	print_lock;
}					t_attrs;

int					parse_args(int ac, char **av, t_attrs *result);

int					ft_numlen(unsigned int x);

int					ft_strlen(const char *string);

char				*get_file_name(char *str);

int					ft_isdigit(char c);

void				ft_putstr(const char *str);

void				ft_putstr_fd(const char *str, int fd);

void				ft_putnbr(unsigned long nbr);

int					ft_atoi(const char *str);

char				*ft_ultoa(unsigned long number, int *result_len);

void				ft_memcpy(void *dst, void *src, size_t size);

int					error(const char *message);

int					usage(char *file_name);

void				safe_lock_mutex(pthread_mutex_t *mutex, char **error);

void				safe_unlock_mutex(pthread_mutex_t *mutex, char **error);

void				ft_usleep(unsigned long time);

void				safe_sem_wait_thread(sem_t *sem, char **error);

void				safe_sem_post_thread(sem_t *sem, char **error);

sem_t				*create_sem(unsigned long init_value, const char *name);

bool				is_died(t_philo_attrs *philo, t_attrs *program);

int					monitor_process(t_attrs *program);

unsigned long		get_current_time_stamp(void);

unsigned long		get_time_offset(unsigned long start_time);

void				print_status(t_attrs *attrs, int id, char *status, bool lock_print);

#endif
