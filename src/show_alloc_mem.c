/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 19:55:24 by marnaud           #+#    #+#             */
/*   Updated: 2019/06/19 21:37:43 by marnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

static int	print_loop(int condition, size_t start, size_t end, size_t size)
{
	if (condition)
	{
		print_mem_addr(start);
		write(1, " - ", 3);
		print_mem_addr(end);
		print_size(size, 1);
		write(1, " octets\n", 8);
		return (size);
	}
	return (0);
}

static int	loop_zone_tiny(void)
{
	int	n;
	int	mem;
	int	i;

	mem = 0;
	n = 0;
	while (g_z.t[n] && n < 4096)
	{
		i = sizeof(int);
		while (i < ((NZONE / getpagesize() + 1)
			* getpagesize()) && i < *(int *)g_z.t[n])
		{
			mem += print_loop(((struct s_h *)(g_z.t[n] + i))->occuped,
				(size_t)((struct s_h *)(g_z.t[n] + i +
					sizeof(struct s_h))), (size_t)((struct s_h *)(g_z.t[n]
					+ i + sizeof(struct s_h) + ((struct s_h *)(g_z.t[n]
						+ i))->size)), ((struct s_h *)(g_z.t[n] + i))->size);
			i += sizeof(struct s_h) + ((struct s_h *)(g_z.t[n] + i))->size;
		}
		i = 0;
		n++;
	}
	return (mem);
}

static int	loop_zone_small(void)
{
	int	n;
	int	mem;
	int	i;

	mem = 0;
	n = 0;
	while (g_z.s[n] && n < 4096)
	{
		i = sizeof(int);
		while (i < ((MZONE / getpagesize() + 1)
			* getpagesize()) && i < *(int *)g_z.s[n])
		{
			mem += print_loop(((struct s_h *)(g_z.s[n] + i))->occuped,
				(size_t)((struct s_h *)(g_z.s[n] + i +
					sizeof(struct s_h))), (size_t)((struct s_h *)(g_z.s[n]
					+ i + sizeof(struct s_h) + ((struct s_h *)(g_z.s[n]
						+ i))->size)), ((struct s_h *)(g_z.s[n] + i))->size);
			i += sizeof(struct s_h) + ((struct s_h *)(g_z.s[n] + i))->size;
		}
		i = 0;
		n++;
	}
	return (mem);
}

static int	loop_zone_large(void)
{
	int n;
	int mem;

	write(1, "LARGE : ", 8);
	print_mem_addr((size_t)g_z.l[0]);
	write(1, "\n", 1);
	mem = 0;
	n = 0;
	while (g_z.l[n] && n < 4096)
	{
		mem += print_loop(((struct s_h *)g_z.l[n])->occuped,
				(size_t)((struct s_h *)(g_z.l[n] + sizeof(struct s_h))),
					(size_t)((struct s_h *)(g_z.l[n] + sizeof(struct s_h) +
						((struct s_h *)g_z.l[n])->size)),
							((struct s_h *)g_z.l[n])->size);
		n++;
	}
	return (mem);
}

void		show_alloc_mem(void)
{
	int mem;

	mem = 0;
	if ((int)g_z.t[0])
	{
		write(1, "TINY : ", 7);
		print_mem_addr((size_t)g_z.t[0]);
		write(1, "\n", 1);
		mem += loop_zone_tiny();
	}
	if ((int)g_z.s[0])
	{
		write(1, "SMALL : ", 7);
		print_mem_addr((size_t)g_z.s[0]);
		write(1, "\n", 1);
		mem += loop_zone_small();
	}
	if ((int)g_z.l[0])
		mem += loop_zone_large();
	write(1, "Total", 5);
	print_size(mem, 1);
	write(1, " octets\n", 8);
}
