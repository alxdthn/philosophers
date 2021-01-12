#include "../../includes/philo_utils.h"
#include "../../includes/philo_print.h"

bool check_is_died(t_philo_attrs *philo_attrs, t_program_attrs *program_attrs) {
	unsigned long current_time;

	if (philo_attrs->eat_count == program_attrs->number_of_times_each_philosopher_must_eat)
		return true;

	current_time = get_current_time_stamp();
	return current_time - philo_attrs->last_meal >= (program_attrs->time_to_die);
}

int monitor_process(t_program_attrs *program) {
	t_philo_attrs *philosopher;
	register int  i;

	while (true) {
		i = 0;
		while (i < program->number_of_philosophers) {
			philosopher = program->philo_attrs[i++];
			if (check_is_died(philosopher, program)) {
				print_status(get_time_offset(program->start_time), philosopher->id, " died\n");
				return EXIT_SUCCESS;
			}
		}
		if (program->error)
			return error(program->error);
		if (usleep(program->monitor_frequency) == -1)
			return error("sleep error\n");
	}
}
