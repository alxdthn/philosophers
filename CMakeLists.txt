cmake_minimum_required(VERSION 3.17)
project(philosophers C)

set(CMAKE_C_STANDARD 11)

add_executable(philo_one
        src/philo_one/philo_one.c
        src/philo_one/philo_one_init.c
        src/philo_one/philo_one_operations.c
        includes/philo_one.h
        src/common/philo_time.c
        src/common/philo_print.c
        src/common/philo_parse.c
        src/common/philo_utils.c
        src/common/philo_mutex.c
        src/common/philo_monitor.c
        src/common/philo_utils_memory.c
        src/common/philo_utils_string.c
        src/common/philo_utils_number.c
        includes/philo_utils.h)

target_include_directories(philo_one PUBLIC includes)

add_executable(philo_two
        src/philo_two/philo_two.c
        src/philo_two/philo_two_exit.c
        src/philo_two/philo_two_init.c
        src/philo_two/philo_two_operations.c
        includes/philo_two.h
        src/common/philo_time.c
        src/common/philo_print.c
        src/common/philo_parse.c
        src/common/philo_monitor.c
        src/common/philo_semaphore.c
        src/common/philo_utils.c
        src/common/philo_utils_memory.c
        src/common/philo_utils_string.c
        src/common/philo_utils_number.c
        includes/philo_utils.h)

target_include_directories(philo_two PUBLIC includes)

add_executable(philo_three
        src/philo_three/philo_three.c
        src/philo_three/philo_three_exit.c
        src/philo_three/philo_three_init.c
        src/philo_three/philo_three_operations.c
        includes/philo_three.h
        src/common/philo_time.c
        src/common/philo_print.c
        src/common/philo_parse.c
        src/common/philo_utils.c
        src/common/philo_utils_memory.c
        src/common/philo_utils_string.c
        src/common/philo_utils_number.c
        src/common/philo_semaphore.c
        src/common/philo_monitor.c)

target_include_directories(philo_three PUBLIC includes)

add_executable(test_ft_ultoa
        test/test_ft_ultoa.c
        src/common/philo_utils_number.c
        src/common/philo_utils_string.c
        includes/philo_utils.h)

target_include_directories(test_ft_ultoa PUBLIC includes)

add_executable(test_ft_atoi
        test/test_ft_atoi.c
        src/common/philo_utils_number.c
        includes/philo_utils.h)

target_include_directories(test_ft_atoi PUBLIC includes)

add_executable(test_strings
        test/test_strings.c
        src/common/philo_utils_string.c
        includes/philo_utils.h)

target_include_directories(test_strings PUBLIC includes)

add_executable(test
        test/test.c)