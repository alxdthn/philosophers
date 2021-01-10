cmake_minimum_required(VERSION 3.17)
project(philosophers C)

set(CMAKE_C_STANDARD 11)

add_executable(philo_one
        philo_one/src/philo_one.c
        philo_one/src/monitor.c
        philo_one/includes/philo_one.h
        common/src/philo_time.c
        common/src/philo_print.c
        common/src/philo_parse.c
        common/src/philo_utils.c
        common/src/philo_utils_memory.c
        common/src/philo_utils_string.c
        common/src/philo_utils_number.c
        common/includes/philo_time.h
        common/includes/philo_print.h
        common/includes/philo_parse.h
        common/includes/philo_utils.h)

target_include_directories(philo_one PUBLIC
        philo_one/includes
        common/includes)

add_executable(test_ft_ultoa
        common/test/test_ft_ultoa.c
        common/src/philo_utils_number.c
        common/includes/philo_utils.h)

target_include_directories(test_ft_ultoa PUBLIC
        common/includes)

add_executable(test_ft_atoi
        common/test/test_ft_atoi.c
        common/src/philo_utils_number.c
        common/includes/philo_utils.h)

target_include_directories(test_ft_atoi PUBLIC
        common/includes)