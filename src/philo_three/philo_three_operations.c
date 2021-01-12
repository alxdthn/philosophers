/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three_operations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 22:31:31 by nalexand          #+#    #+#             */
/*   Updated: 2021/01/12 22:59:30 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"
#include "philo_print.h"

int		eating(t_philo_three *program)
{
	t_program_attrs	*program_attrs;
	t_philo_attrs	*philo_attrs;
	unsigned long	time_offset;

	program_attrs = &program->prog_attrs;
	philo_attrs = program->philosopher_attrs;
	philo_attrs->eat_count++;
	philo_attrs->last_meal = get_current_time_stamp();
	time_offset = get_time_offset(program_attrs->start_time);
	print_status(time_offset, philo_attrs->id, " is eating\n");
	if (usleep(program_attrs->time_to_eat) == -1)
		return (error("error sleep\n"));
	return (0);
}

int		sleeping(t_philo_three *program)
{
	t_program_attrs	*program_attrs;
	t_philo_attrs	*philo_attrs;
	unsigned long	time_offset;

	program_attrs = &program->prog_attrs;
	philo_attrs = program->philosopher_attrs;
	time_offset = get_time_offset(program_attrs->start_time);
	print_status(time_offset, philo_attrs->id, " is sleeping\n");
	if (usleep(program_attrs->time_to_sleep) == -1)
		return (error("error sleep\n"));
	return (0);
}

void	thinking(t_philo_three *program)
{
	t_program_attrs	*program_attrs;
	t_philo_attrs	*philo_attrs;
	unsigned long	time_offset;

	program_attrs = &program->prog_attrs;
	philo_attrs = program->philosopher_attrs;
	time_offset = get_time_offset(program_attrs->start_time);
	print_status(time_offset, philo_attrs->id, " is thinking\n");
}

int		take_forks(t_philo_three *program)
{
	t_program_attrs	*program_attrs;
	t_philo_attrs	*philo_attrs;
	unsigned long	time_offset;

	program_attrs = &program->prog_attrs;
	philo_attrs = program->philosopher_attrs;
	if (sem_wait(program->forks_sem) == -1)
		return (error("error sem wait\n"));
	time_offset = get_time_offset(program_attrs->start_time);
	print_status(time_offset, philo_attrs->id, " has taken a fork\n");
	if (sem_wait(program->forks_sem) == -1)
		return (error("error sem wait\n"));
	time_offset = get_time_offset(program_attrs->start_time);
	print_status(time_offset, philo_attrs->id, " has taken a fork\n");
	return (0);
}

int		drop_forks(t_philo_three *program)
{
	if (sem_post(program->forks_sem) == -1)
		return (error("error sem post\n"));
	if (sem_post(program->forks_sem) == -1)
		return (error("error sem post\n"));
	return (0);
}
