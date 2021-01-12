/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 22:34:59 by nalexand          #+#    #+#             */
/*   Updated: 2021/01/12 22:59:30 by nalexand         ###   ########.fr       */
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
	if (pthread_detach(philosopher->thread))
		pthread_exit(NULL);
	if (philosopher->attrs.id % 2 == 0)
		safe_sleep_thread(EVEN_PHILO_THREAD_START_DELAY, &program->attrs.error);
	while (!program->attrs.error)
	{
		take_forks(philosopher, program);
		eating(philosopher, program);
		drop_forks(program);
		sleeping(philosopher, program);
		thinking(philosopher, program);
	}
	return (NULL);
}

static bool	run_philosophers(t_philo_two *program)
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
	t_philo_two	program;
	sem_t		*sem;

	memset(&program, '\0', sizeof(t_philo_two));
	program.attrs.monitor_frequency = MONITOR_FREQUENCY_USEC;
	if (parse_args(ac, av, &program.attrs))
		return (exit_program(NULL, EXIT_SUCCESS));
	sem = create_semaphore(program.attrs.n_philo);
	if (sem == SEM_FAILED)
		return (exit_program(NULL, error("error create semaphore\n")));
	program.forks_sem = sem;
	if (!create_philosophers(&program))
		return (exit_program(sem, error("error init philosophers\n")));
	if (!run_philosophers(&program))
		return (exit_program(sem, error("error run philosophers\n")));
	return (exit_program(sem, monitor_process(&program.attrs)));
}
