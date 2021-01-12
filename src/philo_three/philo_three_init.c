/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 22:29:55 by nalexand          #+#    #+#             */
/*   Updated: 2021/01/12 22:30:27 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

bool	create_philosophers(t_philo_three *program)
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
