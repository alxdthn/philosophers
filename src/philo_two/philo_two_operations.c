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
	print_status(&program->attrs, philo->attrs.id, EAT, LOCK_PRINT);
	usleep(program->attrs.time_to_eat);
}

void	sleeping(t_philo *philo, t_philo_two *program)
{
	print_status(&program->attrs, philo->attrs.id, SLEEP, LOCK_PRINT);
	usleep(program->attrs.time_to_sleep);
}

void	thinking(t_philo *philo, t_philo_two *program)
{
	print_status(&program->attrs, philo->attrs.id, THINK, LOCK_PRINT);
}

void	take_forks(t_philo *philo, t_philo_two *program)
{
	pthread_mutex_lock(&program->fork_taking_mutex);
	sem_wait(program->forks_sem);
	print_status(&program->attrs, philo->attrs.id, FORK, LOCK_PRINT);
	sem_wait(program->forks_sem);
	print_status(&program->attrs, philo->attrs.id, FORK, LOCK_PRINT);
	pthread_mutex_unlock(&program->fork_taking_mutex);
}

void	drop_forks(t_philo_two *program)
{
	sem_post(program->forks_sem);
	sem_post(program->forks_sem);
}
