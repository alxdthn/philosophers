#ifndef PHILOSOPHERS_PHILO_PARSE_H
# define PHILOSOPHERS_PHILO_PARSE_H

# define MICRO_SEC_IN_MILLIS 1000

typedef struct s_parse_result {
	int number_of_philosophers;
	int time_to_eat;
	int time_to_sleep;
	int time_to_die;
	int number_of_times_each_philosopher_must_eat;
} t_parse_result;

int parse_args(int ac, char **av, t_parse_result *result);

#endif //PHILOSOPHERS_PHILO_PARSE_H
