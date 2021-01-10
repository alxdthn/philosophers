#include "philosophers.h"

long get_current_time_stamp() {
	struct timeval time;

	gettimeofday(&time, NULL);
	return time.tv_sec * 1000 + time.tv_usec / 1000;
}

long get_time_offset(t_program *program)
{
	return get_current_time_stamp() - program->start_time;
}
