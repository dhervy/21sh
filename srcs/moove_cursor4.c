/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove_cursor4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhervy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 16:50:51 by dhervy            #+#    #+#             */
/*   Updated: 2017/04/02 16:51:00 by dhervy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sh.h"

void	ft_copy_line2(t_all *all, char **line, int init, unsigned long buf)
{
	if (buf == LEFT && all->pos_x > 0)
	{
		ft_caps("sc", 0);
		if (all->pos_x <= init)
			ft_caps("mr", 0);
		ft_putchar((*line)[all->pos_x]);
		ft_caps("rc", 0);
		ft_caps("me", 0);
		ft_move_left(all, *line);
	}
	if (buf == RIGHT && all->pos_x < all->size - 2)
	{
		ft_caps("sc", 0);
		if (all->pos_x >= init)
			ft_caps("mr", 0);
		ft_putchar((*line)[all->pos_x]);
		ft_caps("rc", 0);
		ft_caps("me", 0);
		ft_move_right(all, *line);
	}
}

int		ft_copy_line4(t_all *all, int nbr, char **line)
{
	nbr = all->pos_x;
	while (all->pos_x > 0)
		ft_move_left(all, *line);
	ft_caps("sc", 0);
	ft_caps("cd", 0);
	ft_putstr(*line);
	ft_caps("rc", 0);
	while (all->pos_x < nbr)
		ft_move_right(all, *line);
	return (nbr);
}
