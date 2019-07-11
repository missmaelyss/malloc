/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiny.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 18:56:05 by marnaud           #+#    #+#             */
/*   Updated: 2019/06/18 19:02:02 by marnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void		regroup_tiny(int starting_i, int n)
{
	int	size;
	int	i;

	i = starting_i;
	size = 0;
	while (i < ((NZONE / getpagesize() + 1)
		* getpagesize()) && i < *(int *)g_z.t[n])
	{
		if (((struct s_h *)(g_z.t[n] + i))->occuped)
			break ;
		size += sizeof(struct s_h)
			+ ((struct s_h *)(g_z.t[n] + i))->size;
		i += sizeof(struct s_h)
			+ ((struct s_h *)(g_z.t[n] + i))->size;
	}
	*(struct s_h *)(g_z.t[n] + starting_i) =
		(struct s_h){0, size - sizeof(struct s_h)};
}

static void	loop_in_tiny(int *n, int *i, size_t *old_size, size_t size)
{
	(*i) = sizeof(int);
	while ((*i) < ((NZONE / getpagesize() + 1)
		* getpagesize()) && (*i) < *(int *)g_z.t[(*n)])
	{
		if (((struct s_h *)(g_z.t[(*n)] + (*i)))->occuped == 0)
			regroup_tiny((*i), (*n));
		if (((struct s_h *)(g_z.t[(*n)] + (*i)))->size
			>= (int)size && ((struct s_h *)(g_z.t[(*n)]
				+ (*i)))->occuped == 0)
		{
			*old_size = ((struct s_h *)(g_z.t[(*n)] + (*i)))->size;
			break ;
		}
		(*i) += sizeof(struct s_h) + ((struct s_h *)(g_z.t[(*n)]
			+ (*i)))->size;
	}
}

int			find_place_tiny(int *n, int *i, size_t *old_size, size_t size)
{
	(*n) = 0;
	*old_size = 0;
	(*i) = sizeof(int);
	while (g_z.t[(*n)] && *n < 4096)
	{
		loop_in_tiny(n, i, old_size, size);
		if ((*i) + size + sizeof(struct s_h)
			< ((NZONE / getpagesize() + 1) * getpagesize()))
			return (1);
		(*n)++;
	}
	return (0);
}

void		*return_new_place_tiny(int n, size_t size)
{
	if (!(g_z.t[n] = mmap(NULL, (NZONE / getpagesize() + 1)
		* getpagesize(), PROT_READ |
			PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)))
		return (NULL);
	*(int *)g_z.t[n] = sizeof(int) + sizeof(struct s_h) + size;
	*(struct s_h *)(g_z.t[n] + sizeof(int)) = (struct s_h){1, size};
	return ((struct s_h *)(g_z.t[n] + sizeof(int)
		+ sizeof(struct s_h)));
}

void		*return_old_place_tiny(int n, int i, size_t old_size, size_t size)
{
	*(struct s_h *)(g_z.t[n] + i) = (struct s_h){1, size};
	if (old_size && old_size > size)
		*(struct s_h *)(g_z.t[n] + i + sizeof(struct s_h) + size) =
			(struct s_h){0, old_size - size - sizeof(struct s_h)};
	else
		*(int *)g_z.t[n] += sizeof(struct s_h) + size;
	return ((struct s_h *)(g_z.t[n] + i + sizeof(struct s_h)));
}
