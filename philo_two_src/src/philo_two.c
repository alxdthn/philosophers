#include "philo_two.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

static void *philosopher_process(void *arg) {
	t_philosopher_process_argument *argument;
	t_philo_two                    *program;
	t_philosopher                  *philosopher;

	argument    = arg;
	program     = argument->program;
	philosopher = argument->philosopher;

	free(argument);
	if (pthread_detach(philosopher->thread))
		pthread_exit(NULL);
	if (philosopher->attrs.id % 2 == 0)
		safe_sleep_thread(EVEN_PHILO_THREAD_START_DELAY, &program->attrs.error);
	while (true) {
		take_forks(philosopher, program);
		eating(philosopher, program);
		drop_forks(program);
		sleeping(philosopher, program);
		thinking(philosopher, program);
	}
	return NULL;
}

static bool run_philosophers(t_philo_two *program) {
	register int                   i;
	t_philosopher                  *philosopher;
	t_philosopher_process_argument *argument;

	i = 0;
	program->attrs.start_time = get_current_time_stamp();

	while (i < program->attrs.number_of_philosophers) {
		philosopher = &program->philosophers[i++];
		philosopher->attrs.last_meal = program->attrs.start_time;

		argument = malloc(sizeof(t_philosopher_process_argument));
		if (!argument)
			return false;

		argument->program     = program;
		argument->philosopher = philosopher;

		if (pthread_create(&philosopher->thread, NULL, philosopher_process, argument))
			return false;
	}
	return true;
}

int main(int ac, char **av) {
	t_philo_two program;

	ft_bzero(&program, sizeof(t_philo_two));
	program.attrs.monitor_frequency = MONITOR_FREQUENCY_USEC;

	if (parse_args(ac, av, &program.attrs))
		return exit_program(NULL, EXIT_SUCCESS);

	program.forks_sem = create_semaphore(program.attrs.number_of_philosophers);
	if (program.forks_sem == SEM_FAILED)
		return exit_program(program.forks_sem, error("error create semaphore\n"));

	if (!create_philosophers(&program))
		return exit_program(program.forks_sem, error("error init philosophers\n"));

	if (!run_philosophers(&program))
		return exit_program(program.forks_sem, error("error run philosophers\n"));

	return exit_program(program.forks_sem, monitor_process(&program.attrs));
}
