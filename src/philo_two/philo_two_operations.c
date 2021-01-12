/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two_operations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 22:47:50 by nalexand          #+#    #+#             */
/*   Updated: 2021/01/12 22:59:30 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"
#include "philo_print.h"

void	eating(t_philo *philosopher, t_philo_two *program)
{
	unsigned long	time_offset;

	philosopher->attrs.eat_count++;
	philosopher->attrs.last_meal = get_current_time_stamp();
	time_offset = get_time_offset(program->attrs.start_time);
	print_status(time_offset, philosopher->attrs.id, " is eating\n");
	safe_sleep_thread(program->attrs.time_to_eat, &program->attrs.error);
}

void	sleeping(t_philo *philosopher, t_philo_two *program)
{
	unsigned long	time_offset;

	time_offset = get_time_offset(program->attrs.start_time);
	print_status(time_offset, philosopher->attrs.id, " is sleeping\n");
	safe_sleep_thread(program->attrs.time_to_sleep, &program->attrs.error);
}

void	thinking(t_philo *philosopher, t_philo_two *program)
{
	unsigned long	time_offset;

	time_offset = get_time_offset(program->attrs.start_time);
	print_status(time_offset, philosopher->attrs.id, " is thinking\n");
}

void	take_forks(t_philo *philosopher, t_philo_two *program)
{
	unsigned long	time_offset;

	safe_sem_wait_thread(program->forks_sem, &program->attrs.error);
	time_offset = get_time_offset(program->attrs.start_time);
	print_status(time_offset, philosopher->attrs.id, " has taken a fork\n");
	safe_sem_wait_thread(program->forks_sem, &program->attrs.error);
	time_offset = get_time_offset(program->attrs.start_time);
	print_status(time_offset, philosopher->attrs.id, " has taken a fork\n");
}

void	drop_forks(t_philo_two *program)
{
	safe_sem_post_thread(program->forks_sem, &program->attrs.error);
	safe_sem_post_thread(program->forks_sem, &program->attrs.error);
}
