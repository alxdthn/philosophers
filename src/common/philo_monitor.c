/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 20:24:35 by nalexand          #+#    #+#             */
/*   Updated: 2021/01/18 22:24:07 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_utils.h"

bool	is_died(t_philo_attrs *philo, t_attrs *program)
{
	unsigned long	current_time;

	current_time = get_current_time_stamp();
	return (current_time - philo->last_meal > program->time_to_die);
}

int		kill_philo(t_attrs *program, t_philo_attrs *philo)
{
	print_status(program, philo->id, DIE);
	return (EXIT_SUCCESS);
}

int		monitor_process(t_attrs *program)
{
	t_philo_attrs	*philo;
	register int	i;
	int				should_kill_by_eat_num;

	while (program->ready_philo_number < program->n_philo)
		usleep(1);
	while (true)
	{
		i = 0;
		should_kill_by_eat_num = 1;
		while (i < program->n_philo)
		{
			philo = program->philo_attrs[i++];
			should_kill_by_eat_num &= philo->eat_count >= program->eat_number;
			if (is_died(philo, program))
				return (kill_philo(program, philo));
		}
		if (program->eat_number != UNSPECIFIED && should_kill_by_eat_num)
			return (kill_philo(program, philo));
		if (program->error)
			return (error(program->error));
		usleep(MONITOR_FREQUENCY_USEC);
	}
}
