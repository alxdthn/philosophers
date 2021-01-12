#include "../../includes/philo_utils.h"

int error(const char *message) {
	ft_putstr_fd(message, 2);
	return 1;
}

int usage() {
	ft_putstr_fd("USAGE: ./philo_one num die eat sleep [n_eat]\n", 1);
	ft_putstr_fd("num: is the number of philosophers and also the number of forks.\n\n", 1);
	ft_putstr_fd("die: is in milliseconds, if a philosopher doesn’t start eating.\n", 1);
	ft_putstr_fd("     ’die’ milliseconds after starting his last meal\n", 1);
	ft_putstr_fd("     or the beginning of the simulation, it dies.\n\n", 1);
	ft_putstr_fd("eat: is in milliseconds and is the time it takes for a philosopher to eat.\n\n", 1);
	ft_putstr_fd("sleep: s in milliseconds and is the time the philosopher will spend sleeping.\n\n", 1);
	ft_putstr_fd("n_eat: argument is optional, if all philosophers eat at least ’n_eat’ ", 1);
	ft_putstr_fd("the simulation will stop.\n", 1);
	return 1;
}

void safe_sleep_thread(unsigned long time, char **error) {
	if (usleep(time) == -1) {
		*error = "sleep error\n";
		pthread_exit(NULL);
	}
}
