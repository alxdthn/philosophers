/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_print.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 22:51:52 by nalexand          #+#    #+#             */
/*   Updated: 2021/01/12 22:51:52 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_PRINT_H
# define PHILO_PRINT_H

# include <stdlib.h>
# include <unistd.h>

# define TIME 0
# define ID 1
# define STATUS 2

void print_status(unsigned long time, int philosopher_id, char *status);

char *ft_ultoa(unsigned long number);

#endif
