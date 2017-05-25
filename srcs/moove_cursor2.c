/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove_cursor2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhervy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 15:11:16 by dhervy            #+#    #+#             */
/*   Updated: 2017/04/02 15:11:23 by dhervy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sh.h"

int		ft_check_bn(char *line, int pos_x)
{
	int		i;

	i = 0;
	while (i <= pos_x)
	{
		if (line[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int		ft_check_first_line_left(t_all *all, char *line)
{
	int		i;
	int		nbr;
	int		c;

	i = 0;
	nbr = 0;
	c = 4;
	while (i < all->pos_x)
	{
		c++;
		if (line[i] == '\n')
		{
			nbr++;
			c = 0;
		}
		if (c == all->winsize.x)
		{
			c = 0;
			nbr++;
		}
		i++;
	}
	return (nbr);
}

int		ft_count_move_left(t_all *all, char *line)
{
	int		i;
	int		nbr;

	i = all->pos_x - 2;
	while (i > 0 && line[i] != '\n')
		i--;
	nbr = ((all->pos_x - 2) - i) % all->winsize.x;
	if (ft_check_first_line_left(all, line) == 0)
		nbr += 5;
	ft_caps("up", 0);
	i = 0;
	while (i++ < all->winsize.x)
		ft_caps("le", 0);
	while (nbr-- >= 0)
		ft_caps("nd", 0);
	return (1);
}

int		ft_check_move_left(t_all *all, char *line)
{
	int		i;

	i = all->pos_x - 1;
	if (!ft_check_bn(line, all->pos_x))
	{
		if ((all->pos_x + 5) % all->winsize.x == 0)
			return (2);
		else
			return (0);
	}
	else
	{
		while (line[i] != '\n')
			i--;
		if ((all->pos_x - i) % all->winsize.x == 0)
			return (2);
		else if (line[all->pos_x] == '\n')
			return (ft_count_move_left(all, line));
		else
			return (0);
	}
}

int		ft_move_left(t_all *all, char *line)
{
	int		i;
	int		ret;

	i = 0;
	ret = -1;
	all->pos_x--;
	if ((ret = ft_check_move_left(all, line)) != 0)
	{
		if (ret == 2)
		{
			ft_caps("up", 0);
			while (i++ < all->winsize.x)
				ft_caps("nd", 0);
		}
	}
	else
		ft_caps("le", 1);
	return (0);
}
