/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one_init2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 22:18:25 by nalexand          #+#    #+#             */
/*   Updated: 2021/01/18 22:18:43 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	print_lock(void)
{
	pthread_mutex_lock(&g_print_mutex);
}

static void	print_unlock(void)
{
	pthread_mutex_unlock(&g_print_mutex);
}

void 		init_print_lock(t_philo_one *program)
{
	pthread_mutex_init(&g_print_mutex, NULL);
	program->attrs.print_lock.lock = print_lock;
	program->attrs.print_lock.unlock = print_unlock;
}
