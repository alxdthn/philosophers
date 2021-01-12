/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 22:45:37 by nalexand          #+#    #+#             */
/*   Updated: 2021/01/12 22:45:48 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

bool	create_philosophers(t_philo_two *program)
{
	register int	i;
	t_philo			*result;
	t_philo_attrs	**philo_attrs;

	result = malloc(sizeof(t_philo) * program->attrs.n_philo);
	if (!result)
		return (false);
	philo_attrs = malloc(sizeof(t_philo_attrs *) * program->attrs.n_philo);
	if (!philo_attrs)
		return (false);
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
	return (true);
}
