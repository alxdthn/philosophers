/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 22:58:16 by nalexand          #+#    #+#             */
/*   Updated: 2021/01/12 22:58:16 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include "philo_utils.h"

typedef struct		s_philo {
	t_philo_attrs	attrs;
	pthread_t		thread;
}					t_philo;

typedef struct		s_philo_two {
	sem_t			*forks_sem;
	t_program_attrs	attrs;
	t_philo			*philosophers;
}					t_philo_two;

typedef struct		s_philo_process_argument {
	t_philo_two		*program;
	t_philo			*philosopher;
}					t_philo_process_argument;

bool				create_philosophers(t_philo_two *program);

int					exit_program(sem_t *sem, int exit_code);

void				eating(t_philo *philosopher, t_philo_two *program);

void				sleeping(t_philo *philosopher, t_philo_two *program);

void				thinking(t_philo *philosopher, t_philo_two *program);

void				take_forks(t_philo *philosopher, t_philo_two *program);

void				drop_forks(t_philo_two *program);

#endif