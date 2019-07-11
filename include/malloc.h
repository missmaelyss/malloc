/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 17:54:48 by marnaud           #+#    #+#             */
/*   Updated: 2019/07/11 17:58:09 by marnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# define NMALLOC 512.0
# define MMALLOC 4096.0
# define NZONE 100.0 * NMALLOC
# define MZONE 100.0 * MMALLOC

# include <stdlib.h>
# include <sys/mman.h>
# include <unistd.h>

void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);
void	show_alloc_mem(void);
void	*return_old_place_tiny(int n, int i, size_t old_size, size_t size);
void	*return_new_place_tiny(int n, size_t size);
int		find_place_tiny(int *n, int *i, size_t *old_size, size_t size);
void	regroup_tiny(int starting_i, int n);
void	*return_old_place_small(int n, int i, size_t old_size, size_t size);
void	*return_new_place_small(int n, size_t size);
int		find_place_small(int *n, int *i, size_t *old_size, size_t size);
void	regroup_small(int starting_i, int n);
void	*malloc_large(size_t size);
void	print_mem_addr(size_t nbr);
void	print_size(size_t size, int start);
void	show_alloc_mem(void);
int		is_in_memory(void *ptr);

struct	s_zone
{
	void	*t[4096];
	void	*s[4096];
	void	*l[4096];
};

struct	s_h
{
	int		occuped;
	int		size;
};

extern struct s_zone	g_z;

#endif
