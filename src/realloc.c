/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 21:45:34 by marnaud           #+#    #+#             */
/*   Updated: 2019/06/19 21:46:04 by marnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

static void	ft_cpy_mem(char *src, char *dest)
{
	int		n;

	n = 0;
	while (n < (((struct s_h *)(dest - sizeof(struct s_h)))->size)
		&& n < (((struct s_h *)(src - sizeof(struct s_h)))->size))
	{
		dest[n] = src[n];
		n++;
	}
}

void		*realloc(void *ptr, size_t size)
{
	void	*tmp;
	void	*space;

	if (ptr == NULL)
		ptr = malloc(size);
	else if (!is_in_memory(ptr))
		return (NULL);
	space = malloc(size);
	tmp = malloc(((struct s_h *)(ptr - sizeof(struct s_h)))->size);
	ft_cpy_mem(ptr, tmp);
	free(ptr);
	free(space);
	ptr = malloc(size);
	ft_cpy_mem(tmp, ptr);
	free(tmp);
	return (ptr);
}
