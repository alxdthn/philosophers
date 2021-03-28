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

sem_t	*create_sem(unsigned long init_value, const char *name)
{
	sem_unlink(name);
	return (sem_open(name, O_CREAT, FORKS_SEM_FLAGS, init_value));
}
