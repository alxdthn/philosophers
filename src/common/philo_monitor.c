/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 20:24:35 by nalexand          #+#    #+#             */
/*   Updated: 2021/01/12 22:59:30 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_utils.h"
#include "philo_print.h"

bool	is_died(t_philo_attrs *philo, t_program_attrs *program)
{
	unsigned long current_time;

	if (philo->eat_count == program->eat_number)
		return (true);
	current_time = get_current_time_stamp();
	return (current_time - philo->last_meal >= (program->time_to_die));
}

int		monitor_process(t_program_attrs *program)
{
	t_philo_attrs	*philosopher;
	register int	i;

	while (true)
	{
		i = 0;
		while (i < program->n_philo)
		{
			philosopher = program->philo_attrs[i++];
			if (is_died(philosopher, program))
			{
				print_status(
						get_time_offset(program->start_time),
						philosopher->id, " died\n");
				return (EXIT_SUCCESS);
			}
		}
		if (program->error)
			return (error(program->error));
		if (usleep(program->monitor_frequency) == -1)
			return (error("sleep error\n"));
	}
}
