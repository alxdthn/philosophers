#include "philo_three.h"

sem_t *create_semaphore(unsigned long init_value) {
	sem_unlink(FORKS_SEMAPHORE_NAME);
	return sem_open(FORKS_SEMAPHORE_NAME, O_CREAT, 0644, init_value);
}

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
		ft_bzero(philo_attrs, sizeof(t_philo_attrs));
		philo_attrs->id = (int) i + 1;
		attrs_array[i++] = philo_attrs;
	}
	program->program_attrs.philo_attrs = attrs_array;
	return true;
}
