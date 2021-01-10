#include "philo_utils.h"


int ft_numlen(unsigned x) {
	if (x >= 1000000000) return 10;
	if (x >= 100000000) return 9;
	if (x >= 10000000) return 8;
	if (x >= 1000000) return 7;
	if (x >= 100000) return 6;
	if (x >= 10000) return 5;
	if (x >= 1000) return 4;
	if (x >= 100) return 3;
	if (x >= 10) return 2;
	return 1;
}

int ft_isdigit(char c) {
	return c >= '0' && c <= '9';
}

char *ft_ultoa(unsigned long number) {
	char *result;
	int  number_len;

	number_len = ft_numlen(number);

	if (!(result = malloc(sizeof(char) * (number_len + 1))))
		return NULL;

	result[number_len] = '\0';
	while (--number_len >= 0) {
		result[number_len] = (char) (number % 10 + '0');
		number /= 10;
	}
	return result;
}

int ft_atoi(const char *str) {

	register int 	i;
	long 			result;
	int 			sign;

	i = 0;
	while (str[i] && str[i] == ' ' && str[i] == '0')
		i++;

	sign = 1;
	if (str[i] == '-') {
		i++;
		sign = -1;
	} else if (str[i] == '+')
		i++;

	result = 0;
	while (str[i] && ft_isdigit(str[i]))
		result = result * 10 + (str[i++] - 48);
	return (int)(result * sign);
}
