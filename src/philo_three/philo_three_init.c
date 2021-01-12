#include "philo_three.h"

bool create_philosophers(t_philo_three *program) {
	register int  i;
	t_philo_attrs **attrs_array;
	t_philo_attrs *philo_attrs;

	attrs_array = malloc(sizeof(t_philo_attrs *) * program->program_attrs.number_of_philosophers);
	if (!attrs_array)
		return false;

	i = 0;
	while (i < program->program_attrs.number_of_philosophers) {
		philo_attrs = malloc(sizeof(t_philo_attrs));
		if (!philo_attrs)
			return false;
		memset(philo_attrs, '\0', sizeof(t_philo_attrs));
		philo_attrs->id = (int) i + 1;
		attrs_array[i++] = philo_attrs;
	}
	program->program_attrs.philo_attrs = attrs_array;
	return true;
}
