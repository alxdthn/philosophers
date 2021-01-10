#include "philo_one.h"
#include "philo_utils.h"
#include "philo_print.h"
#include "philo_time.h"

void monitor_process(t_program *program) {
	t_philosopher *philosophers;
	t_philosopher *philosopher;
	long          current_time;
	register int  i;

	while (TRUE) {
		philosophers = program->philosophers;
		i            = 0;
		while (i < program->attrs.number_of_philosophers) {
			current_time = get_current_time_stamp();
			philosopher  = &philosophers[i++];
			if (philosopher->error) {
				exit(EXIT_FAILURE);
			}
			if (philosopher->status != EATING && current_time - philosopher->last_eating > program->attrs.time_to_die) {
				print_status(get_time_offset(program->start_time), philosopher->id, " died\n");
				exit(EXIT_SUCCESS);
			}
		}
		usleep(program->monitor_frequency);
	}
}

