#include "../../includes/philo_two.h"

int exit_program(sem_t *sem, int exit_code) {
	if (sem) {
		while (sem_post(sem) != -1) {

		}
		sem_close(sem);
		sem_unlink(FORKS_SEMAPHORE_NAME);
	}
	return exit_code;
}
