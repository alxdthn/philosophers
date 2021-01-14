/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one_operations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 22:15:26 by nalexand          #+#    #+#             */
/*   Updated: 2021/01/14 18:13:18 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	eating(t_philo *philo, t_philo_one *program)
{
	philo->attrs.eat_count++;
	philo->attrs.last_meal = get_current_time_stamp();
	print_status(&program->attrs, philo->attrs.id, EAT);
	safe_sleep_thread(program->attrs.time_to_eat, &program->attrs.error);
}

void	sleeping(t_philo *philo, t_philo_one *program)
{
	print_status(&program->attrs, philo->attrs.id, SLEEP);
	safe_sleep_thread(program->attrs.time_to_sleep, &program->attrs.error);
}

void	thinking(t_philo *philo, t_philo_one *program)
{
	print_status(&program->attrs, philo->attrs.id, THINK);
}

void 	take_forks(t_philo *philo, t_philo_one *program)
{
	safe_lock_mutex(philo->left_hand_fork, &program->attrs.error);
	print_status(&program->attrs, philo->attrs.id, FORK);
	safe_lock_mutex(philo->right_hand_fork, &program->attrs.error);
	print_status(&program->attrs, philo->attrs.id, FORK);
}

void	drop_forks(t_philo *philo, t_philo_one *program)
{
	safe_unlock_mutex(philo->right_hand_fork, &program->attrs.error);
	safe_unlock_mutex(philo->left_hand_fork, &program->attrs.error);
}
