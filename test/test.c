//
// Created by Natalia Alexandria on 1/15/21.
//

#include <printf.h>
#include <string.h>

int     ft_intlen_base(unsigned int nbr, int base)
{
	int i;

	i = 0;
	if (nbr == 0)
		return 1;
	while (nbr)
	{
		nbr /= base;
		i++;
	}
	return (i);
}

char *ft_putnbr_base_fd(unsigned int nbr, int base)
{
	static char		buf[50];
	register int	len;
	char			c;

	//	a = W; A = 7
	len = ft_intlen_base(nbr, base);
	buf[len--] = '\0';
	while (len >= 0)
	{
		c = (char)(nbr % base);
		buf[len--] = c + ((c > 9) ? 'W' : '0');
		nbr /= base;
	}
	return buf;
}

void test(unsigned int nbr)
{
	char 	*nbr_str = ft_putnbr_base_fd(nbr, 16);
	printf("%s = %x (%zu)\n", nbr_str, nbr, strlen(nbr_str));
}

int main(void)
{
	int i = 0;
	while (i < 0xFFF)
		test(i++);
}