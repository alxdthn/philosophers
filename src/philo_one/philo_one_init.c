#include "../../includes/philo_one.h"

bool create_philosophers(t_philo_one *program) {
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
		result[i].attrs.id        = (int) i + 1;
		result[i].left_hand_fork  = &program->forks[(i < program->attrs.number_of_philosophers) ? i : 0];
		result[i].right_hand_fork = &program->forks[(i + 1 > program->attrs.number_of_philosophers - 1) ? 0 : i + 1];
		philo_attrs[i] = &result[i].attrs;
		i++;
	}
	program->philosophers      = result;
	program->attrs.philo_attrs = philo_attrs;
	return true;
}

bool create_forks(t_philo_one *program) {
	pthread_mutex_t *result;
	register int    i;

	result = malloc(sizeof(pthread_mutex_t) * program->attrs.number_of_philosophers);
	if (!result)
		return false;

	i = 0;
	while (i < program->attrs.number_of_philosophers) {
		if (pthread_mutex_init(&result[i++], NULL))
			return false;
	}
	program->forks = result;
	return true;
}
