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

typedef struct		s_philo_three {
	bool			is_child;
	pid_t			*children_pid;
	sem_t			*forks_sem;
	t_philo_attrs	*philosopher_attrs;
	t_program_attrs	prog_attrs;
	pthread_t		monitor;
}					t_philo_three;

bool				create_philosophers(t_philo_three *program);

int					exit_program(t_philo_three *program, int exit_code);

int					eating(t_philo_three *program);

int					sleeping(t_philo_three *program);

int					take_forks(t_philo_three *program);

int					drop_forks(t_philo_three *program);

void				thinking(t_philo_three *program);

#endif
