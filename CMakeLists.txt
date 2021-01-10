cmake_minimum_required(VERSION 3.17)
project(philosophers C)

set(CMAKE_C_STANDARD 11)

add_executable(philo_one
        philo_one/src/philo_one.c
        philo_one/src/philo_one_init.c
        philo_one/src/philo_one_operations.c
        philo_one/includes/philo_one.h
        common/src/philo_time.c
        common/src/philo_print.c
        common/src/philo_parse.c
        common/src/philo_utils.c
        common/src/philo_mutex.c
        common/src/philo_monitor.c
        common/src/philo_utils_memory.c
        common/src/philo_utils_string.c
        common/src/philo_utils_number.c
        common/includes/philo_print.h
        common/includes/philo_utils.h)

target_include_directories(philo_one PUBLIC
        philo_one/includes
        common/includes)

add_executable(philo_two
        philo_two/src/philo_two.c
        philo_two/src/philo_two_exit.c
        philo_two/src/philo_two_init.c
        philo_two/src/philo_two_operations.c
        philo_two/includes/philo_two.h
        common/src/philo_time.c
        common/src/philo_print.c
        common/src/philo_parse.c
        common/src/philo_monitor.c
        common/src/philo_semaphore.c
        common/src/philo_utils.c
        common/src/philo_utils_memory.c
        common/src/philo_utils_string.c
        common/src/philo_utils_number.c
        common/includes/philo_print.h
        common/includes/philo_utils.h)

target_include_directories(philo_two PUBLIC
        philo_two/includes
        common/includes)

add_executable(philo_three
        philo_three/src/philo_three.c
        philo_three/src/philo_three_exit.c
        philo_three/src/philo_three_init.c
        philo_three/includes/philo_three.h
        common/src/philo_time.c
        common/src/philo_print.c
        common/src/philo_parse.c
        common/src/philo_utils.c
        common/src/philo_utils_memory.c
        common/src/philo_utils_string.c
        common/src/philo_utils_number.c
        common/src/philo_semaphore.c
        common/src/philo_monitor.c philo_three/src/philo_three_operations.c)

target_include_directories(philo_three PUBLIC
        philo_three/includes
        common/includes)

add_executable(test_ft_ultoa
        common/test/test_ft_ultoa.c
        common/src/philo_utils_number.c
        common/src/philo_utils_string.c
        common/includes/philo_utils.h)

target_include_directories(test_ft_ultoa PUBLIC
        common/includes)

add_executable(test_ft_atoi
        common/test/test_ft_atoi.c
        common/src/philo_utils_number.c
        common/includes/philo_utils.h)

target_include_directories(test_ft_atoi PUBLIC
        common/includes)