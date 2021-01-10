#include "philosophers.h"

void monitor_process(t_program *program) {
	t_philosopher *philosophers;
	t_philosopher *philosopher;
	long          current_time;
	register int  i;

	while (TRUE) {
		philosophers = program->philosophers;
		i            = 0;
		while (i < program->number_of_philosophers) {
			current_time = get_current_time_stamp();
			philosopher  = &philosophers[i++];
			if (philosopher->error) {
				printf("ERROR: %ld ms %d %s\n", current_time, philosopher->id, philosopher->error);
				exit(EXIT_FAILURE);
			}
			if (philosopher->status != EATING && current_time - philosopher->last_eating > program->time_to_die) {
				printf("%ld ms %d died\n", get_time_offset(program), philosopher->id);
				exit(EXIT_SUCCESS);
			}
		}
		usleep(program->monitor_frequency);
	}
}

