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
	philo->attrs.last_meal = get_current_time_stamp();
	print_status(&program->attrs, philo->attrs.id, EAT, LOCK_PRINT);
	philo->attrs.eat_count++;
	usleep(program->attrs.time_to_eat);
}

void	sleeping(t_philo *philo, t_philo_one *program)
{
	print_status(&program->attrs, philo->attrs.id, SLEEP, LOCK_PRINT);
	usleep(program->attrs.time_to_sleep);
}

void	thinking(t_philo *philo, t_philo_one *program)
{
	print_status(&program->attrs, philo->attrs.id, THINK, LOCK_PRINT);
}

void	take_forks(t_philo *philo, t_philo_one *program)
{
    pthread_mutex_lock(&program->fork_taking_mutex);
    pthread_mutex_lock(philo->right_hand_fork);
    print_status(&program->attrs, philo->attrs.id, FORK, LOCK_PRINT);
    pthread_mutex_lock(philo->left_hand_fork);
    print_status(&program->attrs, philo->attrs.id, FORK, LOCK_PRINT);
    pthread_mutex_unlock(&program->fork_taking_mutex);
}

void	drop_forks(t_philo *philo, t_philo_one *program)
{
    pthread_mutex_unlock(philo->left_hand_fork);
    print_status(&program->attrs, philo->attrs.id, " has drop fork\n", LOCK_PRINT);
    pthread_mutex_unlock(philo->right_hand_fork);
    print_status(&program->attrs, philo->attrs.id, " has drop fork\n", LOCK_PRINT);
}
