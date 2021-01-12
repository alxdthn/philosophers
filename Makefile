OBJ_DIR = obj/

PHILO_ONE_INCLUDES = -I philo_one_src/includes \
                     -I common/includes

PHILO_ONE_SRC = philo_one_src/src/philo_one.c \
                philo_one_src/src/philo_one_init.c \
                philo_one_src/src/philo_one_operations.c \
                common/src/philo_time.c \
                common/src/philo_print.c \
                common/src/philo_parse.c \
                common/src/philo_utils.c \
                common/src/philo_mutex.c \
                common/src/philo_monitor.c \
                common/src/philo_utils_memory.c \
                common/src/philo_utils_string.c \
                common/src/philo_utils_number.c

PHILO_ONE_OBJ = $(addprefix $(OBJ_DIR), $(patsubst %.c, %.o, $(PHILO_ONE_SRC)))

all: philo_one

philo_one: philo_one_lib
	gcc $(CFLAGS) -o $@ $< $(PHILO_ONE_INCLUDES)

philo_one_lib: $(PHILO_ONE_OBJ)
	ar rc $^

$(OBJ_DIR)%.o: %.c
	mkdir -p $(dir $@)
	gcc -o $@ -c $< $(PHILO_ONE_INCLUDES)

.PHONY : philo_one