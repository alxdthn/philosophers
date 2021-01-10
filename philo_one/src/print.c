#include "philosophers.h"

void print_char(char c)
{
	write(1, &c, 1);
}

void print_number(unsigned long time)
{
	/*char 	c;

	if (time > 10)
		print_number(time / 10);

	c = (char)(time % 10 + '0');
	print_char(c);*/

	printf("%ld", time);
}

int get_string_len(const char *string)
{
	register int 	i;

	i = 0;
	while (string[i])
	{
		if (string[i] &&
			string[i + 1] &&
			string[i + 2] &&
			string[i + 3] &&
			string[i + 4] &&
			string[i + 5] &&
			string[i + 6] &&
			string[i + 7])
			i += 8;
		else
			i++;
	}
	return i;
}

void print_string(const char *string)
{
	write(1, string, get_string_len(string));
}

void print_status(long time, int philosopher_id, char *status)
{
	print_number(time);
	print_string(" ms ");
	print_number(philosopher_id);
	print_char(' ');
	print_string(status);
	print_char('\n');
}