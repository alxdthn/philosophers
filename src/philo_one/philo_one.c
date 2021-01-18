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
	philosopher->attrs.last_meal = program->attrs.start_time;
	free(argument);
	pthread_detach(philosopher->thread);
	program->attrs.ready_philo_number++;
	if (philosopher->attrs.id % 2 == 0)
		ft_usleep(program->attrs.time_to_eat / 8);
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

static bool	run_philosophers(t_philo_one *program)
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
		if (!argument)
			return (false);
		argument->program = program;
		argument->philosopher = philosopher;
		if (pthread_create(&philosopher->thread, NULL, philo_process, argument))
			return (false);
	}
	return (true);
}

int			main(int ac, char **av)
{
	t_philo_one	program;

	memset(&program, '\0', sizeof(t_philo_one));
	if (parse_args(ac, av, &program.attrs))
		return (1);
	if (!create_forks(&program))
		return (error("error init forks\n"));
	if (pthread_mutex_init(&program.fork_taking_mutex, NULL))
		return (error("error pthread mutex init\n"));
	if (!create_philosophers(&program))
		return (error("error init philosophers\n"));
	if (!init_print_lock(&program))
		return (error("error init print mutex"));
	if (!run_philosophers(&program))
		return (error("error run philosophers\n"));
	return (monitor_process(&program.attrs));
}
