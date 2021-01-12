/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 22:21:40 by nalexand          #+#    #+#             */
/*   Updated: 2021/01/12 22:59:30 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"
#include "philo_print.h"

static void	*monitor_thread(void *arg)
{
	t_philo_three	*program;
	t_philo_attrs	*philosopher;
	unsigned long	time_offset;

	program = arg;
	philosopher = program->philosopher_attrs;
	while (true)
	{
		if (is_died(philosopher, &program->prog_attrs))
		{
			time_offset = get_time_offset(program->prog_attrs.start_time);
			print_status(time_offset, philosopher->id, " died\n");
			exit(SIGCHLD);
		}
		if (program->prog_attrs.error)
			exit(error(program->prog_attrs.error));
		if (usleep(program->prog_attrs.monitor_frequency) == -1)
			exit(error("sleep error\n"));
	}
}

static int	philosopher_process(t_philo_three *program)
{
	t_philo_attrs	*philo_attrs;

	philo_attrs = program->philosopher_attrs;
	if (philo_attrs->id % 2 == 0)
	{
		if (usleep(EVEN_PHILO_THREAD_START_DELAY) == -1)
			return (error("error sleep\n"));
	}
	while (true)
	{
		if (take_forks(program) ||
			eating(program) ||
			drop_forks(program) ||
			sleeping(program))
			return (EXIT_FAILURE);
		thinking(program);
	}
}

static bool	fork_philosophers(t_philo_three *program)
{
	register int	i;
	t_philo_attrs	*philo_attrs;
	pid_t			pid;

	i = 0;
	program->children_pid = malloc(sizeof(pid_t));
	if (!program->children_pid)
		return (false);
	while (i < program->prog_attrs.n_philo)
	{
		pid = fork();
		program->is_child = pid == 0;
		philo_attrs = program->prog_attrs.philo_attrs[i];
		philo_attrs->last_meal = get_current_time_stamp();
		if (pid == 0)
		{
			program->philosopher_attrs = philo_attrs;
			return (true);
		}
		else if (pid > 0)
			program->children_pid[i++] = pid;
		else
			return (false);
	}
	return (true);
}

static int	resolve_fork(t_philo_three *program)
{
	register int	i;

	if (program->is_child)
	{
		if (pthread_create(&program->monitor, NULL, monitor_thread, program))
			return (exit_program(program, error("pthread_create\n")));
		return (philosopher_process(program));
	}
	else
	{
		i = 0;
		while (i < program->prog_attrs.n_philo)
			waitpid(program->children_pid[i++], NULL, WUNTRACED);
		return (exit_program(program, EXIT_SUCCESS));
	}
}

int			main(int ac, char **av)
{
	t_philo_three program;

	memset(&program, '\0', sizeof(t_philo_three));
	program.prog_attrs.monitor_frequency = MONITOR_FREQUENCY_USEC;
	if (parse_args(ac, av, &program.prog_attrs))
		return (exit_program(NULL, EXIT_SUCCESS));
	program.forks_sem = create_semaphore(program.prog_attrs.n_philo);
	if (program.forks_sem == SEM_FAILED)
		return (exit_program(&program, error("error create semaphore\n")));
	if (!create_philosophers(&program))
		return (exit_program(&program, error("error init philosophers\n")));
	program.prog_attrs.start_time = get_current_time_stamp();
	if (!fork_philosophers(&program))
		return (exit_program(&program, error("error run philosophers\n")));
	return (resolve_fork(&program));
}
