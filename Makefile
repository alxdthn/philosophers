VPATH = src/common:src/philo_one:src/philo_two:src/philo_three:includes

PHILO_ONE = philo_one
PHILO_TWO = philo_two
PHILO_THREE = philo_three

CFLAGS = -Wall -Werror -Wextra

OBJD = obj/

INCLUDES = includes/

HEADERS =			$(INCLUDES)philo_one.h \
					$(INCLUDES)philo_two.h \
					$(INCLUDES)philo_three.h \
					$(INCLUDES)philo_utils.h

COMMON_SRC =		src/common/philo_monitor.c \
            		src/common/philo_mutex.c \
            		src/common/philo_parse.c \
            		src/common/philo_print.c \
            		src/common/philo_semaphore.c \
            		src/common/philo_time.c \
            		src/common/philo_utils.c \
            		src/common/philo_utils_memory.c \
            		src/common/philo_utils_number.c \
            		src/common/philo_utils_string.c
COMMON_OBJ =		$(addprefix $(OBJD), $(patsubst %.c, %.o, $(COMMON_SRC)))

PHILO_ONE_SRC =		src/philo_one/philo_one.c \
               		src/philo_one/philo_one_init.c \
               		src/philo_one/philo_one_init2.c \
               		src/philo_one/philo_one_operations.c
PHILO_ONE_OBJ =		$(addprefix $(OBJD), $(patsubst %.c, %.o, $(PHILO_ONE_SRC)))

PHILO_TWO_SRC =		src/philo_two/philo_two.c \
               		src/philo_two/philo_two_exit.c \
               		src/philo_two/philo_two_init.c \
               		src/philo_two/philo_two_operations.c
PHILO_TWO_OBJ =		$(addprefix $(OBJD), $(patsubst %.c, %.o, $(PHILO_TWO_SRC)))

PHILO_THREE_SRC =	src/philo_three/philo_three.c \
                 	src/philo_three/philo_three_exit.c \
                 	src/philo_three/philo_three_init.c \
                 	src/philo_three/philo_three_operations.c
PHILO_THREE_OBJ =	$(addprefix $(OBJD), $(patsubst %.c, %.o, $(PHILO_THREE_SRC)))

all: $(PHILO_ONE) $(PHILO_TWO) $(PHILO_THREE)

$(PHILO_ONE): $(PHILO_ONE_OBJ) $(COMMON_OBJ)
	@gcc $(CFLAGS) -o $@ $^ -I $(INCLUDES)
	@printf "\x1b[32mCompile executable: "
	@printf $@
	@printf "\x1b[0m\n"

$(PHILO_TWO): $(PHILO_TWO_OBJ) $(COMMON_OBJ)
	@gcc $(CFLAGS) -o $@ $^ -I $(INCLUDES)
	@printf "\x1b[32mCompile executable: "
	@printf $@
	@printf "\x1b[0m\n"

$(PHILO_THREE): $(PHILO_THREE_OBJ) $(COMMON_OBJ)
	@gcc $(CFLAGS) -o $@ $^ -I $(INCLUDES)
	@printf "\x1b[32mCompile executable: "
	@printf $@
	@printf "\x1b[0m\n"

$(OBJD)%.o: %.c $(HEADERS)
	@mkdir -p $(dir $@)
	@gcc $(CFLAGS) -o $@ -c $< -I $(INCLUDES)
	@printf "\x1b[33mCompile object: "
	@printf $(notdir $@)
	@printf "\x1b[0m\n"

$(OBJD):
	mkdir -p $@

clean:
	rm -rf $(OBJD)

fclean: clean
	rm -f $(PHILO_ONE)
	rm -f $(PHILO_TWO)
	rm -f $(PHILO_THREE)

re: fclean all

uniq = $(if $1,$(firstword $1) $(call uniq,$(filter-out $(firstword $1),$1)))