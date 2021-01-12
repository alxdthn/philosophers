#include "philo_one.h"
#include "philo_print.h"

void eating(t_philosopher *philosopher, t_philo_one *program) {
	philosopher->attrs.eat_count++;
	philosopher->attrs.last_meal = get_current_time_stamp();
	print_status(get_time_offset(program->attrs.start_time), philosopher->attrs.id, " is eating\n");
	safe_sleep_thread(program->attrs.time_to_eat, &program->attrs.error);
}

void sleeping(t_philosopher *philosopher, t_philo_one *program) {
	print_status(get_time_offset(program->attrs.start_time), philosopher->attrs.id, " is sleeping\n");
	safe_sleep_thread(program->attrs.time_to_sleep, &program->attrs.error);
}

void thinking(t_philosopher *philosopher, t_philo_one *program) {
	print_status(get_time_offset(program->attrs.start_time), philosopher->attrs.id, " is thinking\n");
}

void take_forks(t_philosopher *philosopher, t_philo_one *program) {
	safe_lock_thread_mutex(&program->fork_taking_mutex, &program->attrs.error);

	safe_lock_thread_mutex(philosopher->left_hand_fork, &program->attrs.error);
	print_status(get_time_offset(program->attrs.start_time), philosopher->attrs.id, " has taken a fork (left)\n");

	safe_lock_thread_mutex(philosopher->right_hand_fork, &program->attrs.error);
	print_status(get_time_offset(program->attrs.start_time), philosopher->attrs.id, " has taken a fork (right)\n");

	safe_unlock_thread_mutex(&program->fork_taking_mutex, &program->attrs.error);
}

void drop_forks(t_philosopher *philosopher, t_philo_one *program) {
	safe_unlock_thread_mutex(philosopher->right_hand_fork, &program->attrs.error);
	safe_unlock_thread_mutex(philosopher->left_hand_fork, &program->attrs.error);
}
