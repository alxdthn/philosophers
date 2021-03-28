/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 21:38:47 by nalexand          #+#    #+#             */
/*   Updated: 2021/01/14 17:54:49 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_utils.h"

int		error(const char *message)
{
	ft_putstr_fd(message, 2);
	return (1);
}

int		usage(char *file_name)
{
	ft_putstr("USAGE: ./");
	ft_putstr(file_name);
	ft_putstr(" num die eat sleep [n_eat]\n");
	ft_putstr("num: is the number of philosophers ");
	ft_putstr("and also the number of forks.\n\n");
	ft_putstr("die: is in milliseconds, if a philosopher ");
	ft_putstr("doesn’t start eating.\n");
	ft_putstr("     ’die’ milliseconds after starting his last meal\n");
	ft_putstr("     or the beginning of the simulation, it dies.\n\n");
	ft_putstr("eat: is in milliseconds and is the time ");
	ft_putstr("it takes for a philosopher to eat.\n\n");
	ft_putstr("sleep: s in milliseconds and is the time ");
	ft_putstr("the philosopher will spend sleeping.\n\n");
	ft_putstr("n_eat: argument is optional, ");
	ft_putstr("if all philosophers eat at least ’n_eat’ ");
	ft_putstr("the simulation will stop.\n");
	return (1);
}
