#include "philo_utils.h"

static void test(char *expected, char *arg)
{
	char	*actual;
	size_t 	actual_len;
	size_t 	expected_len;

	actual = get_file_name(arg);
	actual_len = ft_strlen(actual);
	expected_len = ft_strlen(expected);
	if (actual_len != ft_strlen(expected) || memcmp(expected, actual, expected_len))
	{
		printf("KO expected %s\n   actual   %s\n", expected, actual);
		exit(0);
	} else
		printf("OK %s\n", expected);
}

int main(void)
{
	test("file", "file");
	test("file", "c/file");
	test("file", "a/b/c/file");
	test("file.c", "file.c");
	test("file.c", "c/file.c");
	test("file.c", "a/b/c/file.c");
	test("", "");
	test("", "/");
	test("", "//");
}
