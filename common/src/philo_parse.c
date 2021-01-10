#include "philo_utils.h"

static int get_and_validate_value(char *arg, int *dst, int ratio) {
	register int i;
	int          value;

	i = 0;
	while (arg[i]) {
		if (!ft_isdigit(arg[i]))
			return 1;
		i++;
	}
	value = ft_atoi(arg) * ratio;
	if (value < 0)
		return 1;
	*dst = value;
	return 0;
}

int parse_args(int ac, char **av, t_program_attrs *result) {
	if (ac < 5 || ac > 6)
		return usage();

	result->number_of_times_each_philosopher_must_eat = UNSPECIFIED;

	if (get_and_validate_value(av[1], &result->number_of_philosophers, 1))
		return error("bad number_of_philosophers\n");
	if (get_and_validate_value(av[2], &result->time_to_die, 1))
		return error("bad time_to_die\n");
	if (get_and_validate_value(av[3], &result->time_to_eat, MICRO_SEC_IN_MILLIS))
		return error("bad time_to_eat\n");
	if (get_and_validate_value(av[4], &result->time_to_sleep, MICRO_SEC_IN_MILLIS))
		return error("bad time_to_sleep\n");
	if (ac == 6 && get_and_validate_value(av[5], &result->number_of_times_each_philosopher_must_eat, 1))
		return error("bad number_of_times_each_philosopher_must_eat\n");
	return 0;
}