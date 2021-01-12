#include "../../includes/philo_two.h"
#include "../../includes/philo_print.h"

void eating(t_philosopher *philosopher, t_philo_two *program) {
	philosopher->attrs.eat_count++;
	philosopher->attrs.last_meal = get_current_time_stamp();
	print_status(get_time_offset(program->attrs.start_time), philosopher->attrs.id, " is eating\n");
	safe_sleep_thread(program->attrs.time_to_eat, &program->attrs.error);
}

void sleeping(t_philosopher *philosopher, t_philo_two *program) {
	print_status(get_time_offset(program->attrs.start_time), philosopher->attrs.id, " is sleeping\n");
	safe_sleep_thread(program->attrs.time_to_sleep, &program->attrs.error);
}

void thinking(t_philosopher *philosopher, t_philo_two *program) {
	print_status(get_time_offset(program->attrs.start_time), philosopher->attrs.id, " is thinking\n");
}

void take_forks(t_philosopher *philosopher, t_philo_two *program) {
	safe_sem_wait_thread(program->forks_sem, &program->attrs.error);
	print_status(get_time_offset(program->attrs.start_time), philosopher->attrs.id, " has taken a fork\n");

	safe_sem_wait_thread(program->forks_sem, &program->attrs.error);
	print_status(get_time_offset(program->attrs.start_time), philosopher->attrs.id, " has taken a fork\n");
}

void drop_forks(t_philo_two *program) {
	safe_sem_post_thread(program->forks_sem, &program->attrs.error);
	safe_sem_post_thread(program->forks_sem, &program->attrs.error);
}
