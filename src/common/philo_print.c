/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 20:54:35 by nalexand          #+#    #+#             */
/*   Updated: 2021/01/13 19:50:15 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_print.h"
#include "philo_utils.h"

static bool	get_numbers(unsigned long time, int philosopher_id, char **strings)
{
	strings[TIME] = ft_ultoa(time);
	strings[ID] = ft_ultoa(philosopher_id);
	if (strings[TIME] && strings[ID])
		return (true);
	free(strings[TIME]);
	free(strings[ID]);
	return (false);
}

static void	get_lens(char **strings, int *lens)
{
	lens[TIME] = ft_strlen(strings[TIME]);
	lens[ID] = ft_strlen(strings[ID]);
	lens[STATUS] = ft_strlen(strings[STATUS]);
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

void		print_status(unsigned long time, int philosopher_id, char *status)
{
	int		lens[3];
	char	*strings[3];

	printf("%ldms %d%s", time, philosopher_id, status);
	return;
	if (!get_numbers(time, philosopher_id, strings))
		return ;
	strings[STATUS] = status;
	get_lens(strings, lens);
	write_line(strings, lens);
	free(strings[TIME]);
	free(strings[ID]);
}
