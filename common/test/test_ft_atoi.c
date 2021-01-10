#include "philo_print.h"
#include "philo_utils.h"
#include <stdio.h>

static void test_ft_atoi(int expected, const char *arg) {
	int actual;

	actual = ft_atoi(arg);

	if (expected < actual) {
		printf("KO \"%d\" actual: %d\n", expected, actual);
		exit(1);
	} else {
		printf("OK \"%d\"\n", expected);
	}
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err34-c"
static void test_ft_atoi_with_original(const char *arg) {
	test_ft_atoi(atoi(arg), arg);
}
#pragma clang diagnostic pop

int main(void) {
	test_ft_atoi(0, "0");
	test_ft_atoi(1, "1");
	test_ft_atoi(2, "2");
	test_ft_atoi(3, "3");
	test_ft_atoi(4, "4");
	test_ft_atoi(5, "5");
	test_ft_atoi(6, "6");
	test_ft_atoi(7, "7");
	test_ft_atoi(8, "8");
	test_ft_atoi(9, "9");
	test_ft_atoi(10, "10");
	test_ft_atoi(11, "11");
	test_ft_atoi(12, "12");
	test_ft_atoi(13, "13");
	test_ft_atoi(14, "14");
	test_ft_atoi(15, "15");
	test_ft_atoi(16, "16");
	test_ft_atoi(17, "17");
	test_ft_atoi(18, "18");
	test_ft_atoi(19, "19");
	test_ft_atoi(210, "210");
	test_ft_atoi(211, "211");
	test_ft_atoi(212, "212");
	test_ft_atoi(213, "213");
	test_ft_atoi(214, "214");
	test_ft_atoi(215, "215");
	test_ft_atoi(216, "216");
	test_ft_atoi(217, "217");
	test_ft_atoi(218, "218");
	test_ft_atoi(219, "219");
	test_ft_atoi(3210, "3210");
	test_ft_atoi(3211, "3211");
	test_ft_atoi(3212, "3212");
	test_ft_atoi(3213, "3213");
	test_ft_atoi(3214, "3214");
	test_ft_atoi(3215, "3215");
	test_ft_atoi(3216, "3216");
	test_ft_atoi(3217, "3217");
	test_ft_atoi(3218, "3218");
	test_ft_atoi(3219, "3219");

	test_ft_atoi(-0, "0");
	test_ft_atoi(-1, "-1");
	test_ft_atoi(-2, "-2");
	test_ft_atoi(-3, "-3");
	test_ft_atoi(-4, "-4");
	test_ft_atoi(-5, "-5");
	test_ft_atoi(-6, "-6");
	test_ft_atoi(-7, "-7");
	test_ft_atoi(-8, "-8");
	test_ft_atoi(-9, "-9");
	test_ft_atoi(-10, "-10");
	test_ft_atoi(-11, "-11");
	test_ft_atoi(-12, "-12");
	test_ft_atoi(-13, "-13");
	test_ft_atoi(-14, "-14");
	test_ft_atoi(-15, "-15");
	test_ft_atoi(-16, "-16");
	test_ft_atoi(-17, "-17");
	test_ft_atoi(-18, "-18");
	test_ft_atoi(-19, "-19");
	test_ft_atoi(-210, "-210");
	test_ft_atoi(-211, "-211");
	test_ft_atoi(-212, "-212");
	test_ft_atoi(-213, "-213");
	test_ft_atoi(-214, "-214");
	test_ft_atoi(-215, "-215");
	test_ft_atoi(-216, "-216");
	test_ft_atoi(-217, "-217");
	test_ft_atoi(-218, "-218");
	test_ft_atoi(-219, "-219");
	test_ft_atoi(-3210, "-3210");
	test_ft_atoi(-3211, "-3211");
	test_ft_atoi(-3212, "-3212");
	test_ft_atoi(-3213, "-3213");
	test_ft_atoi(-3214, "-3214");
	test_ft_atoi(-3215, "-3215");
	test_ft_atoi(-3216, "-3216");
	test_ft_atoi(-3217, "-3217");
	test_ft_atoi(-3218, "-3218");
	test_ft_atoi(-3219, "-3219");

	test_ft_atoi_with_original("--");
	test_ft_atoi_with_original("-+");
	test_ft_atoi_with_original("+-");
	test_ft_atoi_with_original("-0");
	test_ft_atoi_with_original("+0");
	test_ft_atoi_with_original("000");
	test_ft_atoi_with_original("0+0");
	test_ft_atoi_with_original("-0+0");
	test_ft_atoi_with_original("1-2");
	test_ft_atoi_with_original("2+1");
	test_ft_atoi_with_original("+1");
	test_ft_atoi_with_original("+42");
	test_ft_atoi_with_original(" +42");
	test_ft_atoi_with_original("\t +42");
	test_ft_atoi_with_original("\n +42");
	test_ft_atoi_with_original("\v +42");
	test_ft_atoi_with_original("\b +42");
	test_ft_atoi_with_original("\t\n\v\b +42");
	test_ft_atoi_with_original("2147483647");
	test_ft_atoi_with_original("2147483648");
	test_ft_atoi_with_original("-2147483648");
	test_ft_atoi_with_original("+2147483647");
	test_ft_atoi_with_original("+2147483648");
	test_ft_atoi_with_original("a42");
	test_ft_atoi_with_original("42a");
}
