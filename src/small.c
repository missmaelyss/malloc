/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 19:13:50 by marnaud           #+#    #+#             */
/*   Updated: 2019/06/18 19:14:00 by marnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void		regroup_small(int starting_i, int n)
{
	int	size;
	int	i;

	i = starting_i;
	size = 0;
	while (i < ((MZONE / getpagesize() + 1)
		* getpagesize()) && i < *(int *)g_z.s[n])
	{
		if (((struct s_h *)(g_z.s[n] + i))->occuped)
			break ;
		size += sizeof(struct s_h)
			+ ((struct s_h *)(g_z.s[n] + i))->size;
		i += sizeof(struct s_h)
			+ ((struct s_h *)(g_z.s[n] + i))->size;
	}
	*(struct s_h *)(g_z.s[n] + starting_i) =
		(struct s_h){0, size - sizeof(struct s_h)};
}

static void	loop_in_small(int *n, int *i, size_t *old_size, size_t size)
{
	(*i) = sizeof(int);
	while ((*i) < ((MZONE / getpagesize() + 1)
		* getpagesize()) && (*i) < *(int *)g_z.s[(*n)])
	{
		if (((struct s_h *)(g_z.s[(*n)] + (*i)))->occuped == 0)
			regroup_small((*i), (*n));
		if (((struct s_h *)(g_z.s[(*n)] + (*i)))->size
			>= (int)size && ((struct s_h *)(g_z.s[(*n)]
				+ (*i)))->occuped == 0)
		{
			*old_size = ((struct s_h *)(g_z.s[(*n)] + (*i)))->size;
			break ;
		}
		(*i) += sizeof(struct s_h) + ((struct s_h *)(g_z.s[(*n)]
			+ (*i)))->size;
	}
}

int			find_place_small(int *n, int *i, size_t *old_size, size_t size)
{
	(*n) = 0;
	*old_size = 0;
	(*i) = sizeof(int);
	while (g_z.s[(*n)])
	{
		loop_in_small(n, i, old_size, size);
		if ((*i) + size + sizeof(struct s_h)
			< ((MZONE / getpagesize() + 1) * getpagesize()))
			return (1);
		(*n)++;
	}
	return (0);
}

void		*return_new_place_small(int n, size_t size)
{
	g_z.s[n] = mmap(NULL, (MZONE / getpagesize() + 1)
		* getpagesize(), PROT_READ |
			PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	*(int *)g_z.s[n] = sizeof(int) + sizeof(struct s_h) + size;
	*(struct s_h *)(g_z.s[n] + sizeof(int)) = (struct s_h){1, size};
	return ((struct s_h *)(g_z.s[n] + sizeof(int)
		+ sizeof(struct s_h)));
}

void		*return_old_place_small(int n, int i, size_t old_size, size_t size)
{
	*(struct s_h *)(g_z.s[n] + i) = (struct s_h){1, size};
	if (old_size && old_size > size)
		*(struct s_h *)(g_z.s[n] + i + sizeof(struct s_h) + size) =
			(struct s_h){0, old_size - size - sizeof(struct s_h)};
	else
		*(int *)g_z.s[n] += sizeof(struct s_h) + size;
	return ((struct s_h *)(g_z.s[n] + i + sizeof(struct s_h)));
}
