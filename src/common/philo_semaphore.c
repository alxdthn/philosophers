/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_semaphore.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 21:15:47 by nalexand          #+#    #+#             */
/*   Updated: 2021/01/12 21:17:55 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_utils.h"

sem_t	*create_semaphore(unsigned long init_value)
{
	sem_unlink(FORKS_SEM_NAME);
	return (sem_open(FORKS_SEM_NAME, O_CREAT, FORKS_SEM_FLAGS, init_value));
}

void	safe_sem_wait_thread(sem_t *sem, char **error)
{
	if (sem_wait(sem) == -1)
	{
		*error = "error sem wait\n";
		pthread_exit(NULL);
	}
}

void	safe_sem_post_thread(sem_t *sem, char **error)
{
	if (sem_post(sem) == -1)
	{
		*error = "error sem wait\n";
		pthread_exit(NULL);
	}
}
