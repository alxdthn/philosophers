#include "philosophers.h"

int error(char *message) {
	printf("%s\n", message);
	return 1;
}

void eating(t_philosopher *philosopher, t_program *program) {
	if (philosopher->status == THINKING) {
		print_status(get_time_offset(program),  philosopher->id, "is eating");
		philosopher->status = EATING;
		usleep(program->time_to_eat);
		philosopher->last_eating = get_current_time_stamp();
	} else {
		philosopher->error = "bad status on eating";
	}
}

void sleeping(t_philosopher *philosopher, t_program *program) {
	if (philosopher->status == EATING) {
		printf("%ld ms %d is sleeping\n", get_time_offset(program), philosopher->id);
		philosopher->status = SLIPPING;
		usleep(program->time_to_sleep);
	} else {
		philosopher->error = "bad status on sleeping";
	}
}

void thinking(t_philosopher *philosopher, t_program *program) {
	if (philosopher->status == SLIPPING) {
		printf("%ld ms %d is thinking\n", get_time_offset(program), philosopher->id);
		philosopher->status = THINKING;
	} else {
		philosopher->error = "bad status on thinking";
	}
}

void take_forks(t_philosopher *philosopher, t_program *program) {
	pthread_mutex_lock(&program->fork_taking_mutex);

	pthread_mutex_lock(philosopher->left_hand_fork);
	printf("%ld ms %d has taken a fork (left)\n", get_time_offset(program), philosopher->id);

	pthread_mutex_lock(philosopher->right_hand_fork);
	printf("%ld ms %d has taken a fork (right)\n", get_time_offset(program), philosopher->id);

	pthread_mutex_unlock(&program->fork_taking_mutex);
}

void drop_forks(t_philosopher *philosopher) {
	pthread_mutex_unlock(philosopher->right_hand_fork);
	pthread_mutex_unlock(philosopher->left_hand_fork);
}

void *philosopher_process(void *arg) {
	t_philosopher_process_argument *argument;
	t_program                      *program;
	t_philosopher                  *philosopher;

	argument    = arg;
	program     = argument->program;
	philosopher = argument->philosopher;

	pthread_detach(philosopher->thread);
	free(argument);
	while (TRUE) {
		take_forks(philosopher, program);
		eating(philosopher, program);
		drop_forks(philosopher);
		sleeping(philosopher, program);
		thinking(philosopher, program);
	}
	return NULL;
}

void create_philosophers(t_program *program) {
	register int  i;
	t_philosopher *result;

	result = malloc(sizeof(t_philosopher) * program->number_of_philosophers);
	if (!result)
		return;

	bzero(result, sizeof(t_philosopher) * program->number_of_philosophers);

	i                     = 0;
	while (i < program->number_of_philosophers) {
		result[i].id              = (int) i + 1;
		result[i].left_hand_fork  = &program->forks[(i < program->number_of_philosophers) ? i : 0];
		result[i].right_hand_fork = &program->forks[(i + 1 > program->number_of_philosophers - 1) ? 0 : i + 1];
		i++;
	}
	program->philosophers = result;
}

void create_forks(t_program *program) {
	pthread_mutex_t *result;
	register int    i;

	result = malloc(sizeof(pthread_mutex_t) * program->number_of_philosophers);
	if (!result)
		return;

	i = 0;
	while (i < program->number_of_philosophers) {
		if (pthread_mutex_init(&result[i++], NULL))
			return;
	}
	program->forks = result;
}

int run_philosophers(t_program *program) {
	register int                   i;
	t_philosopher                  *philosopher;
	t_philosopher_process_argument *argument;

	i = 0;
	program->start_time = get_current_time_stamp();

	while (i < program->number_of_philosophers) {
		philosopher = &program->philosophers[i++];
		philosopher->last_eating = program->start_time;

		argument = malloc(sizeof(t_philosopher_process_argument));
		if (!argument)
			return FALSE;

		argument->program     = program;
		argument->philosopher = philosopher;

		if (pthread_create(&philosopher->thread, NULL, philosopher_process, argument))
			return FALSE;
	}
	return TRUE;
}

int get_value(char *arg, int *dst, int ratio) {
	register int i;
	int          value;

	i = 0;
	while (arg[i]) {
		if (arg[i] < '0' || arg[i] > '9')
			return 1;
		i++;
	}
	value = atoi(arg) * ratio;
	if (value < 0)
		return 1;
	*dst = value;
	return 0;
}

int parse_args(int ac, char **av, t_program *program) {
	if (ac < 5 || ac > 6)
		return error(
				"USAGE: ./philo_one number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]");
	if (get_value(av[1], &program->number_of_philosophers, 1))
		return error("bad number_of_philosophers");
	if (get_value(av[2], &program->time_to_die, 1))
		return error("bad time_to_die");
	if (get_value(av[3], &program->time_to_eat, MICRO_SEC_IN_MILLIS))
		return error("bad time_to_eat");
	if (get_value(av[4], &program->time_to_sleep, MICRO_SEC_IN_MILLIS))
		return error("bad time_to_sleep");
	if (ac == 6 && get_value(av[5], &program->number_of_times_each_philosopher_must_eat, 1))
		return error("bad number_of_times_each_philosopher_must_eat");
	return 0;
}

int main(int ac, char **av) {
	t_program program;

	bzero(&program, sizeof(t_program));

	program.monitor_frequency                         = MONITOR_FREQUENCY;
	program.number_of_times_each_philosopher_must_eat = 1;

	if (parse_args(ac, av, &program))
		return 1;

	create_forks(&program);
	if (!program.forks)
		return error("error init forks");

	if (pthread_mutex_init(&program.fork_taking_mutex, NULL))
		return error("error pthread mutex init");

	create_philosophers(&program);
	if (!program.philosophers)
		return error("error init philosophers");

	if (!run_philosophers(&program))
		return error("error run philosophers");

	monitor_process(&program);
	return (0);
}
