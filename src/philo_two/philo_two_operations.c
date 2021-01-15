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

void	eating(t_philo *philo, t_philo_two *program)
{
	philo->attrs.eat_count++;
	philo->attrs.last_meal = get_current_time_stamp();
	print_status(&program->attrs, philo->attrs.id, EAT);
	ft_usleep(program->attrs.time_to_eat);
}

void	sleeping(t_philo *philo, t_philo_two *program)
{
	print_status(&program->attrs, philo->attrs.id, SLEEP);
	ft_usleep(program->attrs.time_to_sleep);
}

void	thinking(t_philo *philo, t_philo_two *program)
{
	print_status(&program->attrs, philo->attrs.id, THINK);
}

void	take_forks(t_philo *philo, t_philo_two *program)
{
	safe_sem_wait_thread(program->forks_sem, &program->attrs.error);
	print_status(&program->attrs, philo->attrs.id, FORK);
	safe_sem_wait_thread(program->forks_sem, &program->attrs.error);
	print_status(&program->attrs, philo->attrs.id, FORK);
}

void	drop_forks(t_philo_two *program)
{
	safe_sem_post_thread(program->forks_sem, &program->attrs.error);
	safe_sem_post_thread(program->forks_sem, &program->attrs.error);
}
