#include "../../includes/philo_utils.h"

void safe_lock_thread_mutex(pthread_mutex_t *mutex, char **error) {
	if (pthread_mutex_lock(mutex)) {
		*error = "bad mutex lock\n";
		pthread_exit(NULL);
	}
}

void safe_unlock_thread_mutex(pthread_mutex_t *mutex, char **error) {
	if (pthread_mutex_unlock(mutex)) {
		*error = "bad mutex unlock\n";
		pthread_exit(NULL);
	}
}
