#include "../../includes/philo_utils.h"

void ft_bzero(void *dst, size_t size) {
	unsigned char *dst_mem;
	register int  i;

	dst_mem = dst;
	i       = 0;
	while (i < size) {
		dst_mem[i] = '\0';
		if (i + 8 < size) {
			dst_mem[i + 1] = '\0';
			dst_mem[i + 2] = '\0';
			dst_mem[i + 3] = '\0';
			dst_mem[i + 4] = '\0';
			dst_mem[i + 5] = '\0';
			dst_mem[i + 6] = '\0';
			dst_mem[i + 7] = '\0';
			i += 8;
		} else {
			i++;
		}
	}
}

void ft_memcpy(void *dst, void *src, size_t size) {
	register size_t i;
	unsigned char   *dst_mem;
	unsigned char   *src_mem;

	dst_mem = dst;
	src_mem = src;

	i = 0;
	while (i < size) {
		dst_mem[i] = src_mem[i];
		if (i + 8 < size) {
			dst_mem[i + 1] = src_mem[i + 1];
			dst_mem[i + 2] = src_mem[i + 2];
			dst_mem[i + 3] = src_mem[i + 3];
			dst_mem[i + 4] = src_mem[i + 4];
			dst_mem[i + 5] = src_mem[i + 5];
			dst_mem[i + 6] = src_mem[i + 6];
			dst_mem[i + 7] = src_mem[i + 7];
			i += 8;
		} else
			i++;
	}
}
