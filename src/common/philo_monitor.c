/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 20:24:35 by nalexand          #+#    #+#             */
/*   Updated: 2021/01/14 18:30:14 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_utils.h"

bool	is_died(t_philo_attrs *philo, t_attrs *program)
{
	unsigned long current_time;

	if (philo->eat_count == program->eat_number)
		return (true);
	current_time = get_current_time_stamp();
	return (current_time - philo->last_meal > program->time_to_die);
}

int		monitor_process(t_attrs *program)
{
	t_philo_attrs	*philo;
	register int	i;

	while (true)
	{
		i = 0;
		while (i < program->n_philo)
		{
			philo = program->philo_attrs[i++];
			if (is_died(philo, program))
			{
				print_status(program, philo->id, DIE);
				return (EXIT_SUCCESS);
			}
		}
		if (program->error)
			return (error(program->error));
	}
}
