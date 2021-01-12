/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 20:54:04 by nalexand          #+#    #+#             */
/*   Updated: 2021/01/12 22:59:30 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_utils.h"

static int	get_and_validate_value(char *arg, int *dst, int ratio)
{
	register int	i;
	int				value;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (1);
		i++;
	}
	value = ft_atoi(arg) * ratio;
	if (value < 0)
		return (1);
	*dst = value;
	return (0);
}

int			parse_args(int ac, char **av, t_program_attrs *result)
{
	if (ac < 5 || ac > 6)
		return (usage(get_file_name(av[0])));
	result->eat_number = UNSPECIFIED;
	if (get_and_validate_value(av[1], &result->n_philo, 1))
		return (error("bad n_philo\n"));
	if (get_and_validate_value(av[2], (int *)&result->time_to_die, 1))
		return (error("bad time_to_die\n"));
	if (get_and_validate_value(av[3], &result->time_to_eat, USEC_IN_MILLIS))
		return (error("bad time_to_eat\n"));
	if (get_and_validate_value(av[4], &result->time_to_sleep, USEC_IN_MILLIS))
		return (error("bad time_to_sleep\n"));
	if (ac == 6 && get_and_validate_value(av[5], &result->eat_number, 1))
		return (error("bad eat_number\n"));
	return (0);
}
