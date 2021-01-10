cmake_minimum_required(VERSION 3.17)
project(philosophers C)

set(CMAKE_C_STANDARD 11)

add_executable(philo_one
        philo_one/src/main.c philo_one/src/monitor.c philo_one/includes/philosophers.h philo_one/src/time.c philo_one/src/print.c)

target_include_directories(philo_one
        PUBLIC philo_one/includes)