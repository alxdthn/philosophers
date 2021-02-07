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

void	eating(t_philo_three *program)
{
	t_attrs			*program_attrs;
	t_philo_attrs	*philo_attrs;

	program_attrs = &program->prog_attrs;
	philo_attrs = program->philosopher_attrs;
	philo_attrs->last_meal = get_current_time_stamp();
	print_status(program_attrs, philo_attrs->id, EAT, LOCK_PRINT);
	philo_attrs->eat_count++;
	if (philo_attrs->eat_count == program->prog_attrs.eat_number)
	{
		drop_forks(program);
		exit(EXIT_BY_EAT_COUNT);
	}
	ft_usleep(program_attrs->time_to_eat);
}

void	sleeping(t_philo_three *program)
{
	t_attrs			*program_attrs;
	t_philo_attrs	*philo_attrs;

	program_attrs = &program->prog_attrs;
	philo_attrs = program->philosopher_attrs;
	print_status(program_attrs, philo_attrs->id, SLEEP, LOCK_PRINT);
	ft_usleep(program_attrs->time_to_sleep);
}

void	thinking(t_philo_three *program)
{
	t_attrs			*program_attrs;
	t_philo_attrs	*philo_attrs;

	program_attrs = &program->prog_attrs;
	philo_attrs = program->philosopher_attrs;
	print_status(program_attrs, philo_attrs->id, THINK, LOCK_PRINT);
}

int		take_forks(t_philo_three *program)
{
	t_attrs			*program_attrs;
	t_philo_attrs	*philo_attrs;

	if (sem_wait(g_forks_taking_sem))
		return (error("error sem wait\n"));
	program_attrs = &program->prog_attrs;
	philo_attrs = program->philosopher_attrs;
	if (sem_wait(program->forks_sem) == -1)
		return (error("error sem wait\n"));
	print_status(program_attrs, philo_attrs->id, FORK, LOCK_PRINT);
	if (sem_wait(program->forks_sem) == -1)
		return (error("error sem wait\n"));
	print_status(program_attrs, philo_attrs->id, FORK, LOCK_PRINT);
	if (sem_post(g_forks_taking_sem))
		return (error("error sem post\n"));
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
