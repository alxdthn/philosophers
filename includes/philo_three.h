/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 22:53:33 by nalexand          #+#    #+#             */
/*   Updated: 2021/01/12 22:59:30 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include "philo_utils.h"
# include <libc.h>

# define PRINT_SEM_NAME	"/philo_three_print"
# define FORKS_TAKING_SEM_NAME "/philo_three_forks_taking"
# define EXIT_BY_STARVATION 12
# define EXIT_BY_EAT_COUNT 13

sem_t				*g_print_sem;
sem_t				*g_forks_taking_sem;

typedef struct		s_philo_three {
	bool			is_child;
	pid_t			*children_pid;
	sem_t			*forks_sem;
	t_philo_attrs	*philosopher_attrs;
	t_attrs			prog_attrs;
	pthread_t		monitor;
}					t_philo_three;

void 				create_philosophers(t_philo_three *program);

void				init_print_lock(t_philo_three *program);

void 				exit_program(t_philo_three *program, int exit_code);

void				eating(t_philo_three *program);

void				sleeping(t_philo_three *program);

void 				take_forks(t_philo_three *program);

void 				drop_forks(t_philo_three *program);

void				thinking(t_philo_three *program);

#endif
