#include <errno.h>
#include "philosophers.h"

int error(char *message) {
	printf("ERROR: %s\n", message);
	return 1;
}

void eating(t_philosopher *philosopher, t_program *program) {
	if (philosopher->status == THINKING) {
		printf("%ld ms %d is eating\n", get_time_offset(program), philosopher->id);
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

void *philosopher_process(void *arg) {
	t_philosopher_process_argument *argument;
	t_program                      *program;
	t_philosopher                  *philosopher;

	argument    = arg;
	program     = argument->program;
	philosopher = argument->philosopher;

	pthread_detach(philosopher->thread);
	free(argument);
	while (program->is_running) {

		pthread_mutex_lock(&program->fork_taking_mutex);

		pthread_mutex_lock(philosopher->left_hand_fork);
		printf("%ld ms %d has taken a fork (left)\n", get_time_offset(program), philosopher->id);

		if (pthread_mutex_lock(philosopher->right_hand_fork) == EBUSY)
		{
			printf("AAA");
			pthread_mutex_unlock(philosopher->left_hand_fork);
		}

		printf("%ld ms %d has taken a fork (right)\n", get_time_offset(program), philosopher->id);

		pthread_mutex_unlock(&program->fork_taking_mutex);

		eating(philosopher, program);

		pthread_mutex_unlock(philosopher->right_hand_fork);
		pthread_mutex_unlock(philosopher->left_hand_fork);

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

int main(void) {
	t_program program;
	pthread_t monitor_thread;

	bzero(&program, sizeof(t_program));

	program.number_of_philosophers = 4;
	program.monitor_frequency      = 1 * 1000 * 9;
	program.time_to_eat            = 1 * 1000 * 1000;
	program.time_to_sleep          = 1 * 1000 * 1000;
	program.time_to_die            = 3 * 1000;
	program.is_running             = TRUE;

	create_forks(&program);
	if (!program.forks)
		return error("init forks");

	pthread_mutex_init(&program.fork_taking_mutex, NULL);

	create_philosophers(&program);
	if (!program.philosophers)
		return error("init philosophers");

	if (!run_philosophers(&program))
		return error("run philosophers");

	if (pthread_create(&monitor_thread, NULL, monitor_process, &program))
		return error("init monitor");

	pthread_join(monitor_thread, NULL);
	return (0);
}
