/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 22:21:40 by nalexand          #+#    #+#             */
/*   Updated: 2021/01/18 22:20:32 by nalexand         ###   ########.fr       */
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
			program->prog_attrs.print_lock.lock();
			print_status(&program->prog_attrs, philosopher->id, DIE, DONT_LOCK);
			exit(EXIT_BY_STARVATION);
		}
		usleep(MONITOR_FREQUENCY_USEC);
	}
}

static void 	philosopher_process(t_philo_three *program)
{
	program->philosopher_attrs->last_meal = get_current_time_stamp();
	while (true)
	{
		take_forks(program);
		eating(program);
		drop_forks(program);
		sleeping(program);
		thinking(program);
	}
}

static void 	fork_philosophers(t_philo_three *program)
{
	register int	i;
	t_philo_attrs	*philo_attrs;
	pid_t			pid;

	i = 0;
	program->children_pid = malloc(sizeof(pid_t) * program->prog_attrs.n_philo);
	while (i < program->prog_attrs.n_philo)
	{
		pid = fork();
		program->is_child = pid == 0;
		philo_attrs = program->prog_attrs.philo_attrs[i];
		philo_attrs->last_meal = get_current_time_stamp();
		if (program->is_child)
		{
			program->philosopher_attrs = philo_attrs;
			return ;
		}
		program->children_pid[i++] = pid;
		usleep(PHILO_START_OFFSET);
	}
}

static void resolve_fork(t_philo_three *program)
{
	int		status;
	int		max_eat_count;

	status = 1;
	max_eat_count = 0;
	if (program->is_child)
	{
		pthread_create(&program->monitor, NULL, monitor_thread, program);
		philosopher_process(program);
	}
	else
	{
		while (!(status & EXIT_BY_STARVATION))
		{
			waitpid(-1, &status, 0);
			if (!(status & EXIT_BY_EAT_COUNT))
				max_eat_count++;
			if (max_eat_count == program->prog_attrs.n_philo)
				break ;
		}
		exit_program(program, EXIT_SUCCESS);
	}
}

int			main(int ac, char **av)
{
	t_philo_three program;

	memset(&program, '\0', sizeof(t_philo_three));
	if (parse_args(ac, av, &program.prog_attrs))
		exit_program(&program, EXIT_SUCCESS);
	program.forks_sem = create_sem(program.prog_attrs.n_philo, FORKS_SEM_NAME);
	init_print_lock(&program);
	g_forks_taking_sem = create_sem(1, FORKS_TAKING_SEM_NAME);
	create_philosophers(&program);
	program.prog_attrs.start_time = get_current_time_stamp();
	fork_philosophers(&program);
	resolve_fork(&program);
}
