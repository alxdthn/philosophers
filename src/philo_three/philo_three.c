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

static void	*monitor_thread(void *arg)
{
	t_philo_three	*program;
	t_philo_attrs	*philosopher;

	program = arg;
	philosopher = program->philosopher_attrs;
	while (true)
	{
		if (is_died(philosopher, &program->prog_attrs))
		{
			print_status(&program->prog_attrs, philosopher->id, DIE);
			exit(EXIT_BY_STARVATION);
		}
		if (program->prog_attrs.error)
		{
			error(program->prog_attrs.error);
			exit(EXIT_BY_ERROR);
		}
		usleep(MONITOR_FREQUENCY_USEC);
	}
}

static int	philosopher_process(t_philo_three *program)
{
	program->philosopher_attrs->last_meal = get_current_time_stamp();
	while (true)
	{
		if (take_forks(program))
			return (EXIT_FAILURE);
		eating(program);
		if (drop_forks(program))
			return (EXIT_FAILURE);
		sleeping(program);
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
	int 	status;
	int 	max_eat_count;

	status = 1;
	max_eat_count = 0;
	if (program->is_child)
	{
		if (pthread_create(&program->monitor, NULL, monitor_thread, program))
			return (exit_program(program, error("pthread_create\n")));
		return (philosopher_process(program));
	}
	else
	{
		while (!(status & EXIT_BY_STARVATION) && !(status & EXIT_BY_ERROR))
		{
			waitpid(-1, &status, 0);
			if (!(status & EXIT_BY_EAT_COUNT))
				max_eat_count++;
			if (max_eat_count == program->prog_attrs.n_philo)
				break;
		}
		return (exit_program(program, EXIT_SUCCESS));
	}
}

int			main(int ac, char **av)
{
	t_philo_three program;

	memset(&program, '\0', sizeof(t_philo_three));
	if (parse_args(ac, av, &program.prog_attrs))
		return (exit_program(NULL, EXIT_SUCCESS));
	program.forks_sem = create_semaphore(program.prog_attrs.n_philo, FORKS_SEM_NAME);
	if (program.forks_sem == SEM_FAILED)
		return (exit_program(&program, error("error create semaphore\n")));
	init_print_lock(&program);
	if (g_print_sem == SEM_FAILED)
		return (exit_program(&program, error("error create semaphore\n")));
	g_forks_taking_sem = create_semaphore(1, FORKS_TAKING_SEM_NAME);
	if (g_forks_taking_sem == SEM_FAILED)
		return (exit_program(&program, error("error create semaphore\n")));
	if (!create_philosophers(&program))
		return (exit_program(&program, error("error init philosophers\n")));
	program.prog_attrs.start_time = get_current_time_stamp();
	if (!fork_philosophers(&program))
		return (exit_program(&program, error("error run philosophers\n")));
	return (resolve_fork(&program));
}
