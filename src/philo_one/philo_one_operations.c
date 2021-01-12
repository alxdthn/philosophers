/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one_operations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 22:15:26 by nalexand          #+#    #+#             */
/*   Updated: 2021/01/12 22:21:12 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include "philo_print.h"

void	eating(t_philo *philo, t_philo_one *program)
{
	unsigned long	time_offset;
	char			*msg;

	philo->attrs.eat_count++;
	philo->attrs.last_meal = get_current_time_stamp();
	time_offset = get_time_offset(program->attrs.start_time);
	msg = " is eating\n";
	print_status(time_offset, philo->attrs.id, msg);
	safe_sleep_thread(program->attrs.time_to_eat, &program->attrs.error);
}

void	sleeping(t_philo *philo, t_philo_one *program)
{
	unsigned long	time_offset;
	char			*msg;

	time_offset = get_time_offset(program->attrs.start_time);
	msg = " is sleeping\n";
	print_status(time_offset, philo->attrs.id, msg);
	safe_sleep_thread(program->attrs.time_to_sleep, &program->attrs.error);
}

void	thinking(t_philo *philosopher, t_philo_one *program)
{
	unsigned long	time_offset;
	char			*msg;

	time_offset = get_time_offset(program->attrs.start_time);
	msg = " is thinking\n";
	print_status(time_offset, philosopher->attrs.id, msg);
}

void	take_forks(t_philo *philosopher, t_philo_one *program)
{
	unsigned long	time_offset;
	char			*msg;

	safe_lock_mutex(&program->fork_taking_mutex, &program->attrs.error);
	safe_lock_mutex(philosopher->left_hand_fork, &program->attrs.error);
	time_offset = get_time_offset(program->attrs.start_time);
	msg = " has taken a fork (left)\n";
	print_status(time_offset, philosopher->attrs.id, msg);
	safe_lock_mutex(philosopher->right_hand_fork, &program->attrs.error);
	time_offset = get_time_offset(program->attrs.start_time);
	msg = " has taken a fork (right)\n";
	print_status(time_offset, philosopher->attrs.id, msg);
	safe_unlock_mutex(&program->fork_taking_mutex, &program->attrs.error);
}

void	drop_forks(t_philo *philosopher, t_philo_one *program)
{
	safe_unlock_mutex(philosopher->right_hand_fork, &program->attrs.error);
	safe_unlock_mutex(philosopher->left_hand_fork, &program->attrs.error);
}
