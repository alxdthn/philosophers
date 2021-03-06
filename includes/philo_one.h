/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 22:50:22 by nalexand          #+#    #+#             */
/*   Updated: 2021/01/14 17:45:26 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include "philo_utils.h"

pthread_mutex_t		g_print_mutex;

typedef struct		s_philo {
	pthread_t		thread;
	t_philo_attrs	attrs;
	pthread_mutex_t	*left_hand_fork;
	pthread_mutex_t	*right_hand_fork;
}					t_philo;

typedef struct		s_philo_one {
	t_attrs			attrs;
	t_philo			*philosophers;
	pthread_mutex_t	fork_taking_mutex;
	pthread_mutex_t	*forks;
}					t_philo_one;

typedef struct		s_philo_process_argument {
	t_philo			*philosopher;
	t_philo_one		*program;
}					t_philo_process_argument;

void 				create_philosophers(t_philo_one *program);

void 				init_print_lock(t_philo_one *program);

void 				create_forks(t_philo_one *program);

void				eating(t_philo *philo, t_philo_one *program);

void				sleeping(t_philo *philo, t_philo_one *program);

void				thinking(t_philo *philo, t_philo_one *program);

void				take_forks(t_philo *philo, t_philo_one *program);

void				drop_forks(t_philo *philo, t_philo_one *program);

#endif
