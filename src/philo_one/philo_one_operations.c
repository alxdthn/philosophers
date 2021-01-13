/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one_operations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 22:15:26 by nalexand          #+#    #+#             */
/*   Updated: 2021/01/13 22:09:15 by nalexand         ###   ########.fr       */
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

void	thinking(t_philo *philo, t_philo_one *program)
{
	unsigned long	time_offset;
	char			*msg;

	time_offset = get_time_offset(program->attrs.start_time);
	msg = " is thinking\n";
	print_status(time_offset, philo->attrs.id, msg);
}

bool	take_forks(t_philo *philo, t_philo_one *program)
{
	unsigned long	time_offset;
	char			*msg;

	if (philo->left_hand_fork->is_busy || philo->right_hand_fork->is_busy)
		return (false);
	safe_lock_mutex(&program->fork_taking_mutex, &program->attrs.error);
	safe_lock_mutex(&philo->left_hand_fork->mutex, &program->attrs.error);
	philo->left_hand_fork->is_busy = true;
	time_offset = get_time_offset(program->attrs.start_time);
	msg = " has taken a fork (left)\n";
	print_status(time_offset, philo->attrs.id, msg);
	safe_lock_mutex(&philo->right_hand_fork->mutex, &program->attrs.error);
	philo->right_hand_fork->is_busy = true;
	time_offset = get_time_offset(program->attrs.start_time);
	msg = " has taken a fork (right)\n";
	print_status(time_offset, philo->attrs.id, msg);
	safe_unlock_mutex(&program->fork_taking_mutex, &program->attrs.error);
	return (true);
}

void	drop_forks(t_philo *philo, t_philo_one *program)
{
	safe_unlock_mutex(&philo->right_hand_fork->mutex, &program->attrs.error);
	philo->right_hand_fork->is_busy = false;
	safe_unlock_mutex(&philo->left_hand_fork->mutex, &program->attrs.error);
	philo->left_hand_fork->is_busy = false;
}
