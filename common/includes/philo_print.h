#ifndef PHILOSOPHERS_PHILO_PRINT_H
# define PHILOSOPHERS_PHILO_PRINT_H

# include <stdlib.h>
# include <unistd.h>

# define TIME 0
# define ID 1
# define STATUS 2

void print_status(unsigned long time, int philosopher_id, char *status);

char *ft_ultoa(unsigned long number);

#endif
