/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 22:29:55 by nalexand          #+#    #+#             */
/*   Updated: 2021/01/18 22:20:43 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static void	print_lock(void)
{
	sem_wait(g_print_sem);
}

static void	print_unlock(void)
{
	sem_post(g_print_sem);
}

void		init_print_lock(t_philo_three *program)
{
	g_print_sem = create_sem(1, PRINT_SEM_NAME);
	program->prog_attrs.print_lock.lock = print_lock;
	program->prog_attrs.print_lock.unlock = print_unlock;
}

bool		create_philosophers(t_philo_three *program)
{
	register int	i;
	t_philo_attrs	**attrs;
	t_philo_attrs	*philo_attrs;

	attrs = malloc(sizeof(t_philo_attrs *) * program->prog_attrs.n_philo);
	if (!attrs)
		return (false);
	i = 0;
	while (i < program->prog_attrs.n_philo)
	{
		philo_attrs = malloc(sizeof(t_philo_attrs));
		if (!philo_attrs)
			return (false);
		memset(philo_attrs, '\0', sizeof(t_philo_attrs));
		philo_attrs->id = i + 1;
		attrs[i++] = philo_attrs;
	}
	program->prog_attrs.philo_attrs = attrs;
	return (true);
}
