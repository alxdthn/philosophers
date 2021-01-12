/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_memory.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 21:43:19 by nalexand          #+#    #+#             */
/*   Updated: 2021/01/12 22:59:30 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_utils.h"

void	ft_memcpy(void *dst, void *src, size_t size)
{
	register size_t	i;
	unsigned char	*dst_mem;
	unsigned char	*src_mem;

	dst_mem = dst;
	src_mem = src;
	i = 0;
	while (i < size)
	{
		dst_mem[i] = src_mem[i];
		if (i + 8 < size)
		{
			dst_mem[i + 1] = src_mem[i + 1];
			dst_mem[i + 2] = src_mem[i + 2];
			dst_mem[i + 3] = src_mem[i + 3];
			dst_mem[i + 4] = src_mem[i + 4];
			dst_mem[i + 5] = src_mem[i + 5];
			dst_mem[i + 6] = src_mem[i + 6];
			dst_mem[i + 7] = src_mem[i + 7];
			i += 8;
		}
		else
			i++;
	}
}
