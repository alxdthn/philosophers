#include "philosophers.h"

void *monitor_process(void *arg) {
	t_program     *program;
	t_philosopher *philosophers;
	t_philosopher *philosopher;
	long          current_time;
	register int  i;

	program = arg;
	while (TRUE) {
		philosophers = program->philosophers;
		i            = 0;
		while (i < program->number_of_philosophers) {
			current_time = get_current_time_stamp();
			philosopher  = &philosophers[i++];
			if (philosopher->error) {
				printf("ERROR: %ld ms %d %s\n", current_time, philosopher->id, philosopher->error);
				pthread_exit(NULL);
			}
			if (philosopher->status != EATING && current_time - philosopher->last_eating > program->time_to_die) {
				printf("%ld ms %d died (error %ld ms)\n", get_time_offset(program), philosopher->id, -(program->time_to_die - (current_time - philosopher->last_eating)));
				pthread_exit(NULL);
			}
		}
		usleep(program->monitor_frequency);
	}
}