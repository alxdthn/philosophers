/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_string.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 21:59:09 by nalexand          #+#    #+#             */
/*   Updated: 2021/01/12 22:59:30 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_utils.h"

int		ft_strlen(const char *string)
{
	register int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] &&
			string[i + 1] &&
			string[i + 2] &&
			string[i + 3] &&
			string[i + 4] &&
			string[i + 5] &&
			string[i + 6] &&
			string[i + 7])
			i += 8;
		else
			i++;
	}
	return (i);
}

void	ft_putstr_fd(const char *str, int fd)
{
	write(fd, str, ft_strlen(str));
}

void	ft_putstr(const char *str)
{
	write(1, str, ft_strlen(str));
}

char	*get_file_name(char *str)
{
	register int	i;

	if (str == NULL)
		return (NULL);
	i = ft_strlen(str);
	if (i == 0)
		return (str);
	while (i-- >= 0)
	{
		if (str[i] == '/')
			return (str + i + 1);
	}
	return (str);
}

void	ft_putnbr(unsigned long nbr)
{
	char 	*nbr_string;
	int 	len;

	nbr_string = ft_ultoa(nbr, &len);
	if (!nbr_string)
		return;
	write(1, nbr_string, len);
	free(nbr_string);
}
