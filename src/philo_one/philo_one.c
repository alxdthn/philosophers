/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 21:59:51 by nalexand          #+#    #+#             */
/*   Updated: 2021/01/18 22:19:44 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	*philo_process(void *arg)
{
	t_philo_process_argument	*argument;
	t_philo_one					*program;
	t_philo						*philosopher;

	argument = arg;
	program = argument->program;
	philosopher = argument->philosopher;
	philosopher->attrs.last_meal = get_current_time_stamp();
	free(argument);
	if (philosopher->attrs.id % 2 == 0)
		usleep(250);
	while (!program->attrs.error)
	{
		take_forks(philosopher, program);
		eating(philosopher, program);
		drop_forks(philosopher, program);
		sleeping(philosopher, program);
		thinking(philosopher, program);
	}
	return (NULL);
}

static void 	run_philosophers(t_philo_one *program)
{
	t_philo_process_argument	*argument;
	t_philo						*philosopher;
	register int				i;

	i = 0;
	program->attrs.start_time = get_current_time_stamp();
	while (i < program->attrs.n_philo)
	{
		philosopher = &program->philosophers[i++];
		argument = malloc(sizeof(t_philo_process_argument));
		argument->program = program;
		argument->philosopher = philosopher;
		philosopher->attrs.last_meal = get_current_time_stamp();
		pthread_create(&philosopher->thread, NULL, philo_process, argument);
		pthread_detach(philosopher->thread);
	}
	program->attrs.is_ready = TRUE;
}

int			main(int ac, char **av)
{
	t_philo_one	program;

	memset(&program, '\0', sizeof(t_philo_one));
	if (parse_args(ac, av, &program.attrs))
		return (1);
	create_forks(&program);
	pthread_mutex_init(&program.fork_taking_mutex, NULL);
	create_philosophers(&program);
	init_print_lock(&program);
	run_philosophers(&program);
	return (monitor_process(&program.attrs));
}
