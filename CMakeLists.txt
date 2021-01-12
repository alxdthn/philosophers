cmake_minimum_required(VERSION 3.17)
project(philosophers C)

set(CMAKE_C_STANDARD 11)

add_executable(philo_one_src
        philo_one_src/src/philo_one.c
        philo_one_src/src/philo_one_init.c
        philo_one_src/src/philo_one_operations.c
        philo_one_src/includes/philo_one.h
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

target_include_directories(philo_one_src PUBLIC
        philo_one_src/includes
        common/includes)

add_executable(philo_two_src
        philo_two_src/src/philo_two.c
        philo_two_src/src/philo_two_exit.c
        philo_two_src/src/philo_two_init.c
        philo_two_src/src/philo_two_operations.c
        philo_two_src/includes/philo_two.h
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

target_include_directories(philo_two_src PUBLIC
        philo_two_src/includes
        common/includes)

add_executable(philo_three_src
        philo_three_src/src/philo_three.c
        philo_three_src/src/philo_three_exit.c
        philo_three_src/src/philo_three_init.c
        philo_three_src/includes/philo_three.h
        common/src/philo_time.c
        common/src/philo_print.c
        common/src/philo_parse.c
        common/src/philo_utils.c
        common/src/philo_utils_memory.c
        common/src/philo_utils_string.c
        common/src/philo_utils_number.c
        common/src/philo_semaphore.c
        common/src/philo_monitor.c philo_three_src/src/philo_three_operations.c)

target_include_directories(philo_three_src PUBLIC
        philo_three_src/includes
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