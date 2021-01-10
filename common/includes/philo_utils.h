#ifndef PHILOSOPHERS_UTILS_H
# define PHILOSOPHERS_UTILS_H

# include <stdlib.h>
# include <unistd.h>

# define FALSE 0
# define TRUE 1

int ft_numlen(unsigned x);

int ft_strlen(const char *string);

int ft_isdigit(char c);

void ft_memcpy(void *dst, void *src, size_t size);

void ft_bzero(void *dst, size_t size);

void ft_putstr(const char *str);

int ft_atoi(const char *str);

int error(const char *message);

#endif
