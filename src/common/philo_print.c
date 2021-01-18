/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 20:54:35 by nalexand          #+#    #+#             */
/*   Updated: 2021/01/14 18:30:14 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_utils.h"

void		print_status(t_attrs *attrs, int id, char *status)
{
	unsigned long	time_offset;

	attrs->print_lock.lock();
	time_offset = get_time_offset(attrs->start_time);
	ft_putnbr(time_offset);
	ft_putstr("ms ");
	ft_putnbr(id);
	ft_putstr(status);
	attrs->print_lock.unlock();
}
