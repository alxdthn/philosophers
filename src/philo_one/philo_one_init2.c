#include "philo_one.h"

static void print_lock(void)
{
	pthread_mutex_lock(&g_print_mutex);
}

static void	print_unlock(void)
{
	pthread_mutex_unlock(&g_print_mutex);
}

bool		init_print_lock(t_philo_one *program)
{
	if (pthread_mutex_init(&g_print_mutex, NULL))
		return false;
	program->attrs.print_lock.lock = print_lock;
	program->attrs.print_lock.unlock = print_unlock;
	return true;
}
