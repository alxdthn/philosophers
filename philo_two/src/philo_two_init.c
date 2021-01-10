#include "philo_two.h"

sem_t *create_semaphore(unsigned long init_value) {
	return sem_open(FORKS_SEMAPHORE_NAME, O_CREAT, 0644, init_value);
}

bool create_philosophers(t_philo_two *program) {
	register int  i;
	t_philosopher *result;
	t_philo_attrs **philo_attrs;

	result = malloc(sizeof(t_philosopher) * program->attrs.number_of_philosophers);
	if (!result)
		return false;

	philo_attrs = malloc(sizeof(t_philo_attrs *) * program->attrs.number_of_philosophers);
	if (!philo_attrs)
		return false;

	ft_bzero(result, sizeof(t_philosopher) * program->attrs.number_of_philosophers);

	i = 0;
	while (i < program->attrs.number_of_philosophers) {
		result[i].attrs.id = (int) i + 1;
		philo_attrs[i] = &result[i].attrs;
		i++;
	}
	program->philosophers      = result;
	program->attrs.philo_attrs = philo_attrs;
	return true;
}
