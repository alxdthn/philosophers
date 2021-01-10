#include <memory.h>
#include "philo_print.h"
#include "philo_utils.h"
#include <stdio.h>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-suspicious-string-compare"

static void test_ultoa(char *expected, unsigned long arg) {
	char *actual;
	int  actual_len;
	int  expected_len;

	actual       = ft_ultoa(arg);
	actual_len   = ft_strlen(actual);
	expected_len = ft_strlen(expected);

	if (actual_len != expected_len || memcmp(expected, actual, expected_len)) {
		printf("KO \"%s\" actual: %s\n", expected, actual);
		exit(1);
	} else {
		printf("OK \"%s\"\n", expected);
	}
	free(actual);
}

int main(void) {
	test_ultoa("0", 0);
	test_ultoa("1", 1);
	test_ultoa("2", 2);
	test_ultoa("3", 3);
	test_ultoa("4", 4);
	test_ultoa("5", 5);
	test_ultoa("6", 6);
	test_ultoa("7", 7);
	test_ultoa("8", 8);
	test_ultoa("9", 9);
	test_ultoa("10", 10);
	test_ultoa("11", 11);
	test_ultoa("12", 12);
	test_ultoa("13", 13);
	test_ultoa("14", 14);
	test_ultoa("15", 15);
	test_ultoa("16", 16);
	test_ultoa("17", 17);
	test_ultoa("18", 18);
	test_ultoa("19", 19);
	test_ultoa("210", 210);
	test_ultoa("211", 211);
	test_ultoa("212", 212);
	test_ultoa("213", 213);
	test_ultoa("214", 214);
	test_ultoa("215", 215);
	test_ultoa("216", 216);
	test_ultoa("217", 217);
	test_ultoa("218", 218);
	test_ultoa("219", 219);
	test_ultoa("3210", 3210);
	test_ultoa("3211", 3211);
	test_ultoa("3212", 3212);
	test_ultoa("3213", 3213);
	test_ultoa("3214", 3214);
	test_ultoa("3215", 3215);
	test_ultoa("3216", 3216);
	test_ultoa("3217", 3217);
	test_ultoa("3218", 3218);
	test_ultoa("3219", 3219);
}