/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 20:24:08 by nalexand          #+#    #+#             */
/*   Updated: 2021/01/12 20:24:22 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_utils.h"

void	safe_lock_mutex(pthread_mutex_t *mutex, char **error)
{
	if (pthread_mutex_lock(mutex))
	{
		*error = "bad mutex lock\n";
		pthread_exit(NULL);
	}
}

void	safe_unlock_mutex(pthread_mutex_t *mutex, char **error)
{
	if (pthread_mutex_unlock(mutex))
	{
		*error = "bad mutex unlock\n";
		pthread_exit(NULL);
	}
}
