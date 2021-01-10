#include "philo_utils.h"

int ft_strlen(const char *string) {
	register int i;

	i = 0;
	while (string[i]) {
		if (string[i] &&
			string[i + 1] &&
			string[i + 2] &&
			string[i + 3] &&
			string[i + 4] &&
			string[i + 5] &&
			string[i + 6] &&
			string[i + 7])
			i += 8;
		else
			i++;
	}
	return i;
}

void ft_putstr(const char *str) {
	write(1, str, ft_strlen(str));
}
