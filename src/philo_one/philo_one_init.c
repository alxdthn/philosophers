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
	int				left_philo_index;
	int				right_philo_index;

	i = 0;
	while (i < program->attrs.n_philo)
	{
		left_philo_index = (i < program->attrs.n_philo) ? i : 0;
		right_philo_index = (i + 1 > program->attrs.n_philo - 1) ? 0 : i + 1;
		res[i].attrs.id = i + 1;
		res[i].left_hand_fork = &program->forks[left_philo_index];
		res[i].right_hand_fork = &program->forks[right_philo_index];
		philo[i] = &res[i].attrs;
		i++;
	}
}

bool		create_philosophers(t_philo_one *program)
{
	t_philo			*result;
	t_philo_attrs	**philo_attrs;

	result = malloc(sizeof(t_philo) * program->attrs.n_philo);
	if (!result)
		return (false);
	philo_attrs = malloc(sizeof(t_philo_attrs *) * program->attrs.n_philo);
	if (!philo_attrs)
		return (false);
	memset(result, '\0', sizeof(t_philo) * program->attrs.n_philo);
	set_data(result, philo_attrs, program);
	program->philosophers = result;
	program->attrs.philo_attrs = philo_attrs;
	return (true);
}

bool		create_forks(t_philo_one *program)
{
	pthread_mutex_t	*result;
	register int	i;

	result = malloc(sizeof(pthread_mutex_t) * program->attrs.n_philo);
	if (!result)
		return (false);
	i = 0;
	while (i < program->attrs.n_philo)
	{
		if (pthread_mutex_init(&result[i++], NULL))
			return (false);
	}
	program->forks = result;
	return (true);
}
