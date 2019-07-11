/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 21:44:59 by marnaud           #+#    #+#             */
/*   Updated: 2019/07/11 17:33:19 by marnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

static int	is_in_tiny(void *ptr)
{
	int n;
	int i;

	n = 0;
	while (g_z.t[n] && n < 4096)
	{
		i = sizeof(int);
		while (i < ((NZONE / getpagesize() + 1)
			* getpagesize()) && i < *(int *)g_z.t[n])
		{
			if (ptr == (g_z.t[n] + i + sizeof(struct s_h)))
				return (1);
			i += sizeof(struct s_h) + ((struct s_h *)(g_z.t[n] + i))->size;
		}
		n++;
	}
	return (0);
}

static int	is_in_small(void *ptr)
{
	int n;
	int i;

	n = 0;
	while (g_z.s[n] && n < 4096)
	{
		i = sizeof(int);
		while (i < ((MZONE / getpagesize() + 1)
			* getpagesize()) && i < *(int *)g_z.s[n])
		{
			if (ptr == (g_z.s[n] + i + sizeof(struct s_h)))
				return (1);
			i += sizeof(struct s_h) + ((struct s_h *)(g_z.s[n] + i))->size;
		}
		n++;
	}
	return (0);
}

static int	is_in_large(void *ptr)
{
	int n;

	n = 0;
	while (g_z.l[n] && n < 4096)
	{
		if (ptr == (g_z.l[n] + sizeof(struct s_h)))
			return (1);
		n++;
	}
	return (0);
}

int			is_in_memory(void *ptr)
{
	if (is_in_tiny(ptr) || is_in_small(ptr) || is_in_large(ptr))
		return (1);
	return (0);
}

void		free(void *ptr)
{
	if (is_in_memory(ptr))
		((struct s_h *)(ptr - sizeof(struct s_h)))->occuped = 0;
}
