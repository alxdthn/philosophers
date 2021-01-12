/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 22:50:22 by nalexand          #+#    #+#             */
/*   Updated: 2021/01/12 22:59:30 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include "philo_utils.h"

typedef struct		s_philo {
	t_philo_attrs	attrs;
	pthread_t		thread;
	pthread_mutex_t	*left_hand_fork;
	pthread_mutex_t	*right_hand_fork;
}					t_philo;

typedef struct		s_philo_one {
	t_program_attrs	attrs;
	pthread_mutex_t	fork_taking_mutex;
	pthread_mutex_t	*forks;
	t_philo			*philosophers;
}					t_philo_one;

typedef struct		s_philo_process_argument {
	t_philo_one		*program;
	t_philo			*philosopher;
}					t_philo_process_argument;

bool				create_philosophers(t_philo_one *program);

bool				create_forks(t_philo_one *program);

void				eating(t_philo *philo, t_philo_one *program);

void				sleeping(t_philo *philo, t_philo_one *program);

void				thinking(t_philo *philosopher, t_philo_one *program);

void				take_forks(t_philo *philosopher, t_philo_one *program);

void				drop_forks(t_philo *philosopher, t_philo_one *program);

#endif
