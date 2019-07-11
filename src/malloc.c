/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 20:44:38 by marnaud           #+#    #+#             */
/*   Updated: 2019/06/17 20:53:24 by marnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void	*malloc(size_t size)
{
	int		n;
	int		i;
	int		space;
	size_t	old_size;

	size = (size / 16 + 1) * 16;
	if (size < NMALLOC)
	{
		space = find_place_tiny(&n, &i, &old_size, size);
		if (space == 0)
			return (return_new_place_tiny(n, size));
		else
			return (return_old_place_tiny(n, i, old_size, size));
	}
	else if (size < MMALLOC)
	{
		space = find_place_small(&n, &i, &old_size, size);
		if (space == 0)
			return (return_new_place_small(n, size));
		else
			return (return_old_place_small(n, i, old_size, size));
	}
	else
		return (malloc_large(size));
}
