/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_address.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 21:41:32 by marnaud           #+#    #+#             */
/*   Updated: 2019/07/11 18:01:10 by marnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

static void	fill_str(char *dest, char *src)
{
	int n;

	n = 0;
	while (src && src[n])
	{
		dest[n] = src[n];
		n++;
	}
}

void		print_mem_addr(size_t nbr)
{
	char	str[11];
	char	alpha[17];
	size_t	max;
	int		row;

	fill_str(str, "0x00000000\0");
	fill_str(alpha, "0123456789ABCDEF\0");
	while (nbr > 0)
	{
		max = 1;
		row = 9;
		while (nbr >= max * 16 && row > 0)
		{
			max *= 16;
			row--;
		}
		str[row] = alpha[(nbr / max)];
		nbr -= (nbr / max) * max;
	}
	write(1, str, 10);
}

void		print_size(size_t size, int start)
{
	char	c;

	if (start)
		write(1, " : ", 3);
	if (size == 0 && start)
		write(1, "0", 1);
	if (size != 0)
	{
		if (size / 10 > 0)
			print_size(size / 10, 0);
		c = 48 + size % 10;
		write(1, &c, 1);
	}
}
