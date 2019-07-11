/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   large.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 19:54:04 by marnaud           #+#    #+#             */
/*   Updated: 2019/06/19 19:54:43 by marnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void	*malloc_large(size_t size)
{
	int	n;

	n = 0;
	while (g_z.l[n])
		n++;
	g_z.l[n] = mmap(NULL, ((sizeof(struct s_h) + size)
		/ getpagesize() + 1) * getpagesize(),
			PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	*(struct s_h *)g_z.l[n] = (struct s_h){1, size};
	return ((struct s_h *)(g_z.l[n] + sizeof(struct s_h)));
}
