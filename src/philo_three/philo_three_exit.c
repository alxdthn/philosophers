/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 22:29:35 by nalexand          #+#    #+#             */
/*   Updated: 2021/01/12 22:59:30 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int	exit_program(t_philo_three *program, int exit_code)
{
	register int	i;

	if (program->children_pid)
	{
		i = 0;
		while (i < program->prog_attrs.n_philo)
			kill(program->children_pid[i++], SIGKILL);
	}
	if (program->forks_sem)
	{
		sem_close(program->forks_sem);
		sem_unlink(FORKS_SEM_NAME);
	}
	return (exit_code);
}
