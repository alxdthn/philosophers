#include "philo_three.h"
#include "philo_print.h"

static void *monitor_thread(void *arg) {
	t_philo_three *program;
	t_philo_attrs *philosopher;

	program = arg;
	philosopher = program->philosopher_attrs;
	while (true) {
		if (check_is_died(philosopher, &program->program_attrs)) {
			print_status(get_time_offset(program->program_attrs.start_time), philosopher->id, " died\n");
			exit(SIGCHLD);
		}
		if (program->program_attrs.error)
			exit(error(program->program_attrs.error));
		if (usleep(program->program_attrs.monitor_frequency) == -1)
			exit(error("sleep error\n"));
	}
}

static int philosopher_process(t_philo_three *program) {
	t_philo_attrs *philo_attrs;

	philo_attrs = program->philosopher_attrs;

	if (philo_attrs->id % 2 == 0) {
		if (usleep(EVEN_PHILO_THREAD_START_DELAY) == -1)
			return error("error sleep\n");
	}
	while (true) {
		if (take_forks(program) ||
			eating(program) ||
			drop_forks(program) ||
			sleeping(program))
			return EXIT_FAILURE;
		thinking(program);
	}
}

static bool fork_philosophers(t_philo_three *program) {
	register int  i;
	t_philo_attrs *philo_attrs;
	pid_t         pid;

	i = 0;
	program->program_attrs.start_time = get_current_time_stamp();
	program->children_pid             = malloc(sizeof(pid_t));
	if (!program->children_pid)
		return false;

	while (i < program->program_attrs.number_of_philosophers) {
		pid = fork();
		program->is_child = pid == 0;
		philo_attrs = program->program_attrs.philo_attrs[i];
		philo_attrs->last_meal = program->program_attrs.start_time;
		if (pid == 0) {
			program->philosopher_attrs = philo_attrs;
			return true;
		} else if (pid > 0) {
			program->children_pid[i++] = pid;
		} else {
			return false;
		}
	}
	return true;
}

static int resolve_fork(t_philo_three *program) {
	register int 	i;

	if (program->is_child) {
		if (pthread_create(&program->monitor, NULL, monitor_thread, program))
			return exit_program(program, error("pthread_create\n"));
		return philosopher_process(program);
	} else {
		i = 0;
		while (i < program->program_attrs.number_of_philosophers)
			waitpid(program->children_pid[i++], NULL, WUNTRACED);
		return exit_program(program, EXIT_SUCCESS);
	}
}

int main(int ac, char **av) {
	t_philo_three program;

	memset(&program, '\0', sizeof(t_philo_three));
	program.program_attrs.monitor_frequency = MONITOR_FREQUENCY_USEC;

	if (parse_args(ac, av, &program.program_attrs))
		return exit_program(NULL, EXIT_SUCCESS);

	program.forks_sem = create_semaphore(program.program_attrs.number_of_philosophers);
	if (program.forks_sem == SEM_FAILED)
		return exit_program(&program, error("error create semaphore\n"));

	if (!create_philosophers(&program))
		return exit_program(&program, error("error init philosophers\n"));

	if (!fork_philosophers(&program))
		return exit_program(&program, error("error run philosophers\n"));

	return resolve_fork(&program);
}
