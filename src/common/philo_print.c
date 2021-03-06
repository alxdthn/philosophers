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


static bool	get_numbers(unsigned long time, int philosopher_id, char **strings, int *lens)
{
	strings[TIME] = ft_ultoa(time, &lens[TIME]);
	strings[ID] = ft_ultoa(philosopher_id, &lens[ID]);
	return (strings[TIME] && strings[ID]);
}

static char	*set_memory(char *dst, char *src, int len)
{
	ft_memcpy(dst, src, len);
	return (dst + len);
}

static void	write_line(char **strings, int *lens)
{
	int		full_len;
	char	*line;
	char	*line_start;

	full_len = lens[TIME] + 3 + lens[ID] + lens[STATUS];
	line = malloc(sizeof(char) * full_len);
	if (!line)
		return ;
	line_start = line;
	line = set_memory(line, strings[TIME], lens[TIME]);
	line = set_memory(line, "ms ", 3);
	line = set_memory(line, strings[ID], lens[ID]);
	set_memory(line, strings[STATUS], lens[STATUS]);
	write(1, line_start, full_len);
	free(line_start);
}

void		print_status(t_attrs *attrs, int id, char *status, bool lock_print)
{
	int				lens[3];
	char			*strings[3];
	unsigned long	time_offset;

	if (lock_print)
		attrs->print_lock.lock();
	time_offset = get_time_offset(attrs->start_time);
	if (get_numbers(time_offset, id, strings, lens))
	{
		strings[STATUS] = status;
		lens[STATUS] = ft_strlen(strings[STATUS]);
		write_line(strings, lens);
	}
	free(strings[TIME]);
	free(strings[ID]);
	if (lock_print)
		attrs->print_lock.unlock();
}
