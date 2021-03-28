/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 22:34:59 by nalexand          #+#    #+#             */
/*   Updated: 2021/01/18 22:20:43 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static void	*philo_process(void *arg)
{
	t_philo_process_argument	*argument;
	t_philo_two					*program;
	t_philo						*philosopher;

	argument = arg;
	program = argument->program;
	philosopher = argument->philosopher;
	free(argument);
	while (true)
	{
		take_forks(philosopher, program);
		eating(philosopher, program);
		drop_forks(program);
		sleeping(philosopher, program);
		thinking(philosopher, program);
	}
	return (NULL);
}

static void 	run_philosophers(t_philo_two *program)
{
	t_philo_process_argument	*argument;
	t_philo						*philosopher;
	register int				i;

	i = 0;
	program->attrs.start_time = get_current_time_stamp();
	while (i < program->attrs.n_philo)
	{
		philosopher = &program->philosophers[i++];
		philosopher->attrs.last_meal = program->attrs.start_time;
		argument = malloc(sizeof(t_philo_process_argument));
		argument->program = program;
		argument->philosopher = philosopher;
		pthread_create(&philosopher->thread, NULL, philo_process, argument);
		pthread_detach(philosopher->thread);
		usleep(PHILO_START_OFFSET);
	}
}

int			main(int ac, char **av)
{
	t_philo_two	program;
	sem_t		*sem;

	memset(&program, '\0', sizeof(t_philo_two));
	if (parse_args(ac, av, &program.attrs))
		return (exit_program(NULL, EXIT_SUCCESS));
	program.forks_sem = create_sem(program.attrs.n_philo, FORKS_SEM_NAME);
	create_philosophers(&program);
	init_print_lock(&program);
	pthread_mutex_init(&program.fork_taking_mutex, NULL);
	run_philosophers(&program);
	return (exit_program(sem, monitor_process(&program.attrs)));
}
