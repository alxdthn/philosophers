#include "philo_one.h"
#include "philo_print.h"
#include "philo_utils.h"
#include "philo_parse.h"
#include "philo_time.h"

void eating(t_philosopher *philosopher, t_program *program) {
	if (philosopher->status == THINKING) {
		print_status(get_time_offset(program->start_time), philosopher->id, " is eating\n");
		philosopher->status = EATING;
		usleep(program->attrs.time_to_eat);
		philosopher->last_eating = get_current_time_stamp();
	} else {
		philosopher->error = "bad status on eating";
	}
}

void sleeping(t_philosopher *philosopher, t_program *program) {
	if (philosopher->status == EATING) {
		print_status(get_time_offset(program->start_time), philosopher->id, " is sleeping\n");
		philosopher->status = SLIPPING;
		usleep(program->attrs.time_to_sleep);
	} else {
		philosopher->error = "bad status on sleeping";
	}
}

void thinking(t_philosopher *philosopher, t_program *program) {
	if (philosopher->status == SLIPPING) {
		print_status(get_time_offset(program->start_time), philosopher->id, " is thinking\n");
		philosopher->status = THINKING;
	} else {
		philosopher->error = "bad status on thinking";
	}
}

void take_forks(t_philosopher *philosopher, t_program *program) {
	pthread_mutex_lock(&program->fork_taking_mutex);

	pthread_mutex_lock(philosopher->left_hand_fork);
	print_status(get_time_offset(program->start_time), philosopher->id, " has taken a fork (left)\n");

	pthread_mutex_lock(philosopher->right_hand_fork);
	print_status(get_time_offset(program->start_time), philosopher->id, " has taken a fork (right)\n");

	pthread_mutex_unlock(&program->fork_taking_mutex);
}

void drop_forks(t_philosopher *philosopher) {
	pthread_mutex_unlock(philosopher->right_hand_fork);
	pthread_mutex_unlock(philosopher->left_hand_fork);
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

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

#pragma clang diagnostic pop

void create_philosophers(t_program *program) {
	register int  i;
	t_philosopher *result;

	result = malloc(sizeof(t_philosopher) * program->attrs.number_of_philosophers);
	if (!result)
		return;

	bzero(result, sizeof(t_philosopher) * program->attrs.number_of_philosophers);

	i                     = 0;
	while (i < program->attrs.number_of_philosophers) {
		result[i].id              = (int) i + 1;
		result[i].left_hand_fork  = &program->forks[(i < program->attrs.number_of_philosophers) ? i : 0];
		result[i].right_hand_fork = &program->forks[(i + 1 > program->attrs.number_of_philosophers - 1) ? 0 : i + 1];
		i++;
	}
	program->philosophers = result;
}

void create_forks(t_program *program) {
	pthread_mutex_t *result;
	register int    i;

	result = malloc(sizeof(pthread_mutex_t) * program->attrs.number_of_philosophers);
	if (!result)
		return;

	i = 0;
	while (i < program->attrs.number_of_philosophers) {
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

	while (i < program->attrs.number_of_philosophers) {
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

int main(int ac, char **av) {
	t_program program;

	ft_bzero(&program, sizeof(t_program));

	program.monitor_frequency                               = MONITOR_FREQUENCY;
	program.attrs.number_of_times_each_philosopher_must_eat = 1;

	if (parse_args(ac, av, &program.attrs))
		return 1;

	create_forks(&program);
	if (!program.forks)
		return error("error init forks\n");

	if (pthread_mutex_init(&program.fork_taking_mutex, NULL))
		return error("error pthread mutex init\n");

	create_philosophers(&program);
	if (!program.philosophers)
		return error("error init philosophers\n");

	if (!run_philosophers(&program))
		return error("error run philosophers\n");

	monitor_process(&program);
	return (0);
}
