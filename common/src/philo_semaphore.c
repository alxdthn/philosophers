#include "philo_utils.h"

void safe_sem_wait_thread(sem_t *sem, char **error) {
	if (sem_wait(sem) == -1) {
		*error = "error sem wait\n";
		pthread_exit(NULL);
	}
}

void safe_sem_post_thread(sem_t *sem, char **error) {
	if (sem_post(sem) == -1) {
		*error = "error sem wait\n";
		pthread_exit(NULL);
	}
}
