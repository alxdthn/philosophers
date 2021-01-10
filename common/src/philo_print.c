#include "philo_print.h"
#include "philo_utils.h"

void print_status(unsigned long time, int philosopher_id, char *status) {
	int  full_len;
	int  len_info[3];
	char *string_info[2];
	char *result;

	string_info[TIME] = ft_ultoa(time);
	string_info[ID]   = ft_ultoa(philosopher_id);
	if (!string_info[TIME] || !string_info[ID])
		return;
	len_info[TIME]   = ft_strlen(string_info[TIME]);
	len_info[ID]     = ft_strlen(string_info[ID]);
	len_info[STATUS] = ft_strlen(status);
	full_len = len_info[TIME] + 4 + len_info[ID] + len_info[STATUS];
	result   = malloc(sizeof(char) * full_len);
	if (result) {
		ft_memcpy(result, string_info[TIME], len_info[TIME]);
		ft_memcpy(result + len_info[TIME], " ms ", 4);
		ft_memcpy(result + len_info[TIME] + 4, string_info[ID], len_info[ID]);
		ft_memcpy(result + len_info[TIME] + 4 + len_info[ID], status, len_info[STATUS]);
		write(1, result, full_len);
	}
	free(string_info[TIME]);
	free(string_info[ID]);
	free(result);
}
