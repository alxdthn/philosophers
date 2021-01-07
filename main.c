#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

void *philosopher(void *arg) {
	printf("AAA");

	pthread_exit(0);
}

typedef struct s_philosopher {
	int id;
} t_philosopher;

typedef struct		s_philosophers {
	t_philosopher	**philosophers;
	size_t 			count;
} 					t_philosophers;

typedef struct		s_threads {
	pthread_t		**threads;
	size_t 			count;
} 					t_threads;

t_philosophers 	*init_philosophers(size_t count) {
	register size_t i;
	t_philosophers	*result;

	result = malloc(sizeof(t_philosophers));
	if (!result)
		return NULL;

	result->philosophers = malloc(sizeof(t_philosopher *) * count);
	if (!result->philosophers)
		return NULL;

	i = 0;
	while (i < count) {
		result->philosophers[i] = malloc(sizeof(t_philosopher));
		if (!result->philosophers[i])
			return NULL;
		memset(result->philosophers[i++], '\0', sizeof(t_philosopher));
	}

	result->count = count;
	return result;
}

t_threads		*init_threads(size_t count) {
	register size_t i;
	t_threads 		*result;

	result = malloc(sizeof(t_threads));
	if (!result)
		return NULL;

	result->threads = malloc(sizeof(pthread_t *) * count);
	if (!result->threads)
		return NULL;

	i = 0;
	while (i < count) {
		pthread_create(result->threads[i], NULL, philosopher, NULL);
		if (!result->threads[i++])
			return NULL;
	}
	return result;
}

int main(void) {
	int 			count = 3;
	t_philosophers	*philosophers;
	t_threads 		*threads;

	philosophers = init_philosophers(count);
	if (!philosophers)
		return EXIT_FAILURE;
	threads = init_threads(count);
	if (!threads)
		return EXIT_FAILURE;
}
