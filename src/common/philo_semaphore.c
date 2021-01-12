#include "philo_utils.h"

sem_t *create_semaphore(unsigned long init_value) {
	sem_unlink(FORKS_SEMAPHORE_NAME);
	return sem_open(FORKS_SEMAPHORE_NAME, O_CREAT, FORKS_SEMAPHORE_FLAGS, init_value);
}

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
