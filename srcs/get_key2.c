/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_key2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhervy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 20:30:35 by dhervy            #+#    #+#             */
/*   Updated: 2017/04/03 20:30:42 by dhervy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sh.h"

void	ft_get_key4(t_all *all, char **line, unsigned long buf)
{
	if (buf == ORIGHT)
	{
		while ((*line)[all->pos_x] != ' ' && all->pos_x < all->size - 1)
			ft_move_right(all, *line);
		while ((*line)[all->pos_x] == ' ' && all->pos_x < all->size - 1)
			ft_move_right(all, *line);
	}
	if (buf == OLEFT)
	{
		while ((*line)[all->pos_x] != ' ' && all->pos_x > 0)
			ft_move_left(all, *line);
		while ((*line)[all->pos_x] == ' ' && all->pos_x > 0)
			ft_move_left(all, *line);
	}
	if ((buf == OC || buf == OX) && *line[0] != '\0')
	{
		ft_copy_line(all, line, buf);
	}
	if (buf == OV && all->copy)
		ft_paste_line(all, line);
}

void	ft_get_key2(t_all *all, char **line, unsigned long buf)
{
	if (buf == ESC)
		exit(0);
	if (buf == LEFT && all->pos_x > 0)
		ft_move_left(all, *line);
	if (buf == RIGHT && all->pos_x < all->size - 1)
		ft_move_right(all, *line);
	if (buf == DEL && all->pos_x > 0)
		ft_delete(all, line);
	if (buf == HOME)
	{
		while (all->pos_x > 0)
			ft_move_left(all, *line);
	}
	if (buf == END)
	{
		while (all->pos_x < all->size - 1)
			ft_move_right(all, *line);
	}
}

void	ft_get_key3(t_all *all, char **line, unsigned long buf)
{
	int		nbr;

	if (buf == OUP)
	{
		nbr = all->pos_x - all->winsize.x;
		if (nbr < 0)
			nbr = 0;
		while (all->pos_x > nbr)
			ft_move_left(all, *line);
	}
	if (buf == ODOWN)
	{
		nbr = all->pos_x + all->winsize.x;
		if (nbr > all->size - 1)
			nbr = all->size - 1;
		while (all->pos_x < nbr)
			ft_move_right(all, *line);
	}
}
