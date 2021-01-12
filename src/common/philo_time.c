#include "../../includes/philo_utils.h"

unsigned long get_current_time_stamp() {
	struct timeval time;

	gettimeofday(&time, NULL);
	return time.tv_sec * 1000 + time.tv_usec / 1000;
}

unsigned long get_time_offset(unsigned long start_time) {
	return get_current_time_stamp() - start_time;
}
