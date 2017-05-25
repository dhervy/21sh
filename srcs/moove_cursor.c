/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove_cursor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhervy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/29 18:21:01 by dhervy            #+#    #+#             */
/*   Updated: 2017/04/01 20:07:03 by dhervy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sh.h"

void	ft_copy_line3bis(t_all *all, char **line, int init)
{
	if (all->pos_x <= init)
	{
		if (all->copy)
			free(all->copy);
		all->copy = ft_strndup(&(*line)[all->pos_x], (init - all->pos_x) + 1);
	}
	else
	{
		if (all->copy)
			free(all->copy);
		all->copy = ft_strndup(&(*line)[init], (all->pos_x - init) + 1);
	}
}

int		ft_copy_line3(char **line, int init, unsigned long key, int nbr)
{
	t_all	*all;

	all = ft_singleton();
	ft_copy_line3bis(all, line, init);
	if (key == OX)
	{
		if (all->pos_x <= init)
		{
			nbr = (init - all->pos_x) + 1;
			while (all->pos_x <= init)
				ft_move_right(all, *line);
			while (nbr-- > 0)
				ft_delete(all, line);
		}
		else if (all->pos_x > init)
		{
			nbr = (all->pos_x - init) + 1;
			ft_move_right(all, *line);
			while (nbr-- > 0)
				ft_delete(all, line);
		}
	}
	else
		nbr = ft_copy_line4(all, nbr, line);
	return (1);
}

int		ft_copy_line5(t_all *all, char **line, int nbr)
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
	return (1);
}

int		ft_copy_line(t_all *all, char **line, unsigned long key)
{
	unsigned long	buf;
	int				init;
	int				nbr;

	nbr = 0;
	init = all->pos_x;
	if (init == all->size - 1)
	{
		ft_move_left(all, *line);
		init--;
	}
	while (42)
	{
		buf = 0;
		read(0, (char*)&buf, 8);
		ft_copy_line2(all, line, init, buf);
		if (buf == ENTER)
			return (ft_copy_line3(line, init, key, nbr));
		if (buf == ESC)
			return (ft_copy_line5(all, line, nbr));
	}
}

void	ft_paste_line(t_all *all, char **line)
{
	int		i;

	i = 0;
	while (all->copy[i])
	{
		*line = (char*)ft_realloc(*line, all->size + 1, all->copy[i], all);
		if (all->pos_x == all->size - 1)
		{
			ft_putchar(all->copy[i]);
			all->pos_x++;
			all->size++;
		}
		else
			ft_write_middle(all, *line);
		i++;
	}
}
