#include "philosophers.h"

void print_char(char c)
{
	write(1, &c, 1);
}

char *u_long_to_string(unsigned long time)
{
	char 			tmp[13];
	char 			*result;
	register int 	i;
	register int 	j;

	i = 0;
	while (time > 10)
	{
		tmp[i++] = (char)(time % 10 + '0');
		time /= 10;
	}

	tmp[i] = (char)(time + '0');
	tmp[i + 1] = '\0';

	if (!(result = malloc(sizeof(char) * 13)))
		return NULL;

	j = 0;
	while (i >= 0)
		result[j++] = tmp[i--];

	return result;
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

void print_status(unsigned long time, int philosopher_id, char *status)
{
	int 	time_string_len;
	int 	id_string_len;
	int 	status_len;
	int 	full_len;
	char 	*time_string;
	char 	*id_string;
	char 	*result;

	time_string = u_long_to_string(time);
	time_string_len = get_string_len(time_string);

	id_string = u_long_to_string(philosopher_id);
	id_string_len = get_string_len(id_string);

	status_len = get_string_len(status);
	full_len = time_string_len + 4 + id_string_len + status_len;

	result = malloc(sizeof(char) * full_len);
	if (time_string && id_string && result) {
		memcpy(result, time_string, time_string_len);
		memcpy(result + time_string_len, " ms ", 4);
		memcpy(result + time_string_len + 4, id_string, 2);
		memcpy(result + time_string_len + 4 + id_string_len, status, status_len);

		write(1, result, full_len);
	}
	free(time_string);
	free(id_string);
	free(result);
}