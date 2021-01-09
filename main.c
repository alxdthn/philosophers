#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <libc.h>

#define EATING 1
#define SLIPPING 2
#define THINKING 3

typedef struct		s_philosopher {
	int				id;
	int				status;
	pthread_mutex_t *left_hand_fork;
	pthread_mutex_t *right_hand_fork;
	long 			last_eating;
	pthread_t 		thread;
}					t_philosopher;

typedef struct		s_program {
	int 			number_of_philosophers;
	int 			time_to_eat;
	int 			time_to_sleep;
	int 			time_to_die;

	long			start_time;

	pthread_mutex_t	mutex;
	pthread_mutex_t	*forks;
	t_philosopher	*philosophers;
}					t_program;

typedef struct 		s_philosopher_process_argument {
	t_program 		*program;
	t_philosopher 	*philosopher;
}					t_philosopher_process_argument;

int  error(char *message)
{
	printf("ERROR: %s\n", message);
	return 1;
}

long get_current_time_stamp() {
	struct timeval time;

	gettimeofday(&time, NULL);
	return time.tv_sec * 1000 + time.tv_usec / 1000;
}

long get_time_offset(t_program *program)
{
	return get_current_time_stamp() - program->start_time;
}

void eating(t_philosopher *philosopher, t_program *program) {
	printf("%ld ms %d is eating\n", get_time_offset(program), philosopher->id);

	philosopher->status = EATING;
	usleep(program->time_to_eat);
	philosopher->last_eating = get_current_time_stamp();
}

void sleeping(t_philosopher *philosopher, t_program *program) {
	char	*status_string;

	if (philosopher->status == EATING)
	{
		printf("%ld ms %d is sleeping\n", get_time_offset(program), philosopher->id);

		philosopher->status = SLIPPING;
		usleep(program->time_to_sleep);
	} else {
		if (philosopher->status == EATING)
			status_string = "EATING";
		else if (philosopher->status == SLIPPING)
			status_string = "SLIPPING";
		else if (philosopher->status == THINKING)
			status_string = "THINKING";
		else
			status_string = "ERROR";
		printf("ERROR: %ld ms %d bad status for sleeping %s\n", get_time_offset(program), philosopher->id, status_string);
		exit(1);
	}
}

void thinking(t_philosopher *philosopher, t_program *program) {
	char	*status_string;

	if (philosopher->status == SLIPPING) {
		printf("%ld ms %d is thinking\n", get_time_offset(program), philosopher->id);
		philosopher->status = THINKING;
	} else {
		if (philosopher->status == EATING)
			status_string = "EATING";
		else if (philosopher->status == SLIPPING)
			status_string = "SLIPPING";
		else if (philosopher->status == THINKING)
			status_string = "THINKING";
		else
			status_string = "ERROR";
		printf("ERROR: %ld ms %d bad status for thinking %s\n", get_time_offset(program), philosopher->id, status_string);
		exit(1);
	}
}

void *monitor_process(void *arg) {
	t_program		*program;
	t_philosopher	*philosophers;
	t_philosopher	*philosopher;
	long 			current_time;
	register int 	i;

	program = arg;
	while (TRUE)
	{
		//printf("monitor: ");
		if (!program->philosophers)
		{
			//printf("wait...\n");
			continue ;
		}
		philosophers = program->philosophers;
		i = 0;
		while (i < program->number_of_philosophers)
		{
			current_time = get_current_time_stamp();
			philosopher = &philosophers[i++];
			//printf("monitor: check %d remaining time %ld ms\n", philosopher->id, program->time_to_die - (current_time - philosopher->last_eating));
			if (philosopher->status != EATING && current_time - philosopher->last_eating > program->time_to_die)
			{
				printf("%ld ms %d died", get_time_offset(program), philosopher->id);
				exit(1);
			}
		}
		usleep(1 * 1000 * 9);
	}
}

void *philosopher_process(void *arg) {
	t_philosopher_process_argument	*argument;
	t_program 						*program;
	t_philosopher					*philosopher;

	argument = arg;
	program = argument->program;
	philosopher = argument->philosopher;
	free(argument);
	while (TRUE) {
		pthread_mutex_lock(philosopher->left_hand_fork);
		printf("%ld ms %d has taken a fork\n", get_time_offset(program), philosopher->id);

		pthread_mutex_lock(philosopher->right_hand_fork);
		printf("%ld ms %d has taken a fork\n", get_time_offset(program), philosopher->id);

		eating(philosopher, program);

		pthread_mutex_unlock(philosopher->left_hand_fork);
		pthread_mutex_unlock(philosopher->right_hand_fork);

		sleeping(philosopher, program);
		thinking(philosopher, program);
	}
}

void create_philosophers(t_program *program){
	register int	i;
	t_philosopher	*result;

	result = malloc(sizeof(t_philosopher) * program->number_of_philosophers);
	if (!result)
		return ;

	bzero(result, sizeof(t_philosopher) * program->number_of_philosophers);

	i = 0;
	while (i < program->number_of_philosophers) {
		result[i].id = (int)i + 1;
		result[i].left_hand_fork = &program->forks[(i < program->number_of_philosophers) ? i : 0];
		result[i].right_hand_fork = &program->forks[(i + 1 > program->number_of_philosophers - 1) ? 0 : i + 1];
		i++;
	}
	program->philosophers = result;
}

void create_forks(t_program *program) {
	pthread_mutex_t		*result;
	register int 		i;

	result = malloc(sizeof(pthread_mutex_t) * program->number_of_philosophers);
	if (!result)
		return ;

	i = 0;
	while (i < program->number_of_philosophers)
	{
		if (pthread_mutex_init(&result[i++], NULL) < 0)
			return;
	}
	program->forks = result;
}

int run_philosophers(t_program *program) {
	register int					i;
	int 							thread_creation_result;
	t_philosopher 					*philosopher;
	t_philosopher_process_argument	*argument;

	i = 0;
	program->start_time = get_current_time_stamp();

	while (i < program->number_of_philosophers)
	{
		philosopher = &program->philosophers[i++];
		philosopher->last_eating = program->start_time;

		argument = malloc(sizeof(t_philosopher_process_argument));
		if (!argument)
			return FALSE;

		argument->program = program;
		argument->philosopher = philosopher;

		thread_creation_result = pthread_create(&philosopher->thread, NULL, philosopher_process, argument);
		if (thread_creation_result < 0)
			return FALSE;
	}
	return TRUE;
}

int main(void) {
	t_program 		program;
	pthread_t 		monitor_thread;
	int 			thread_creation_result;

	bzero(&program, sizeof(t_program));

	program.number_of_philosophers = 4;
	program.time_to_eat = 1 * 1000 * 1000;
	program.time_to_sleep = 1 * 1000 * 1000;
	program.time_to_die = 3 * 1000;

	create_forks(&program);
	if (!program.forks)
		return error("init forks");

	pthread_mutex_init(&program.mutex, NULL);

	create_philosophers(&program);
	if (!program.philosophers)
		return error("init philosophers");

	if (!run_philosophers(&program))
		return error("run philosophers");

	thread_creation_result = pthread_create(&monitor_thread, NULL, monitor_process, &program);
	if (thread_creation_result < 0)
		return error("init monitor");

	pthread_join(monitor_thread, NULL);
}
