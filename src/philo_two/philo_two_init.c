/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 22:45:37 by nalexand          #+#    #+#             */
/*   Updated: 2021/01/18 22:22:57 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static void	print_lock(void)
{
	pthread_mutex_lock(&g_print_mutex);
}

static void	print_unlock(void)
{
	pthread_mutex_unlock(&g_print_mutex);
}

void 		init_print_lock(t_philo_two *program)
{
	pthread_mutex_init(&g_print_mutex, NULL);
	program->attrs.print_lock.lock = print_lock;
	program->attrs.print_lock.unlock = print_unlock;
}

void 		create_philosophers(t_philo_two *program)
{
	register int	i;
	t_philo			*result;
	t_philo_attrs	**philo_attrs;

	result = malloc(sizeof(t_philo) * program->attrs.n_philo);
	philo_attrs = malloc(sizeof(t_philo_attrs *) * program->attrs.n_philo);
	memset(result, '\0', sizeof(t_philo) * program->attrs.n_philo);
	i = 0;
	while (i < program->attrs.n_philo)
	{
		result[i].attrs.id = i + 1;
		philo_attrs[i] = &result[i].attrs;
		i++;
	}
	program->philosophers = result;
	program->attrs.philo_attrs = philo_attrs;
}
