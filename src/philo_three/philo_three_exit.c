#include "../../includes/philo_three.h"

int exit_program(t_philo_three *program, int exit_code) {
	register int	i;

	if (program->children_pid) {
		i = 0;
		while (i < program->program_attrs.number_of_philosophers) {
			kill(program->children_pid[i++], SIGKILL);
		}
	}
	if (program->forks_sem) {
		sem_close(program->forks_sem);
		sem_unlink(FORKS_SEMAPHORE_NAME);
	}
	return exit_code;
}

