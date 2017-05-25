/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhervy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/17 18:58:19 by dhervy            #+#    #+#             */
/*   Updated: 2017/04/01 20:07:15 by dhervy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sh.h"

void	*ft_realloc(void *line, int newsize, char c, t_all *all)
{
	unsigned char	*tmp;

	tmp = (unsigned char*)ft_memalloc(sizeof(unsigned char*) * newsize);
	if (all->size < newsize)
	{
		ft_memcpy(tmp, (unsigned char*)line, all->pos_x);
		ft_memcpy(&tmp[all->pos_x], &c, 1);
		ft_memcpy(&tmp[all->pos_x + 1], &line[all->pos_x], \
			(all->size - 1) - all->pos_x);
	}
	else if (all->size > newsize)
	{
		if (all->pos_x > 1)
			ft_memcpy(tmp, (unsigned char *)line, all->pos_x - 1);
		ft_memcpy(&tmp[all->pos_x - 1], &line[all->pos_x], (all->size - 1));
	}
	free(line);
	return (tmp);
}
