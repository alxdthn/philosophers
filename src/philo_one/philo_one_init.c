/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 22:03:35 by nalexand          #+#    #+#             */
/*   Updated: 2021/01/12 22:59:30 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	set_data(t_philo *res, t_philo_attrs **philo, t_philo_one *program)
{
	register int	i;
	pthread_mutex_t *current_fork;
	pthread_mutex_t *next_fork;

	i = 0;
	while (i < program->attrs.n_philo)
	{
		res[i].attrs.id = i + 1;
		current_fork = &program->forks[i];
		next_fork = &program->forks[(i + 1) % program->attrs.n_philo];
		if (res[i].attrs.id == program->attrs.n_philo)
		{
			res[i].left_hand_fork = next_fork;
			res[i].right_hand_fork = current_fork;
		}
		else
		{
			res[i].left_hand_fork = current_fork;
			res[i].right_hand_fork = next_fork;
		}
		philo[i] = &res[i].attrs;
		i++;
	}
}

void 		create_philosophers(t_philo_one *program)
{
	t_philo			*result;
	t_philo_attrs	**philo_attrs;

	result = malloc(sizeof(t_philo) * program->attrs.n_philo);
	philo_attrs = malloc(sizeof(t_philo_attrs *) * program->attrs.n_philo);
	memset(result, '\0', sizeof(t_philo) * program->attrs.n_philo);
	set_data(result, philo_attrs, program);
	program->philosophers = result;
	program->attrs.philo_attrs = philo_attrs;
}

void 		create_forks(t_philo_one *program)
{
	pthread_mutex_t		*result;
	register int		i;

	result = malloc(sizeof(pthread_mutex_t) * program->attrs.n_philo);
	i = 0;
	while (i < program->attrs.n_philo)
		pthread_mutex_init(&result[i++], NULL);
	program->forks = result;
}
