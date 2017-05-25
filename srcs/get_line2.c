/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhervy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 21:15:26 by dhervy            #+#    #+#             */
/*   Updated: 2017/04/03 21:15:34 by dhervy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sh.h"

void	ft_do_up(int nbr)
{
	int		i;

	i = 0;
	while (i++ < nbr)
		ft_caps("do", 0);
	i = 0;
	while (i++ < nbr)
		ft_caps("up", 0);
}

void	ft_write_middle2(t_all *all, char *str)
{
	if ((all->pos_x + 5) % all->winsize.x == 0)
	{
		ft_putchar(str[all->pos_x]);
		ft_caps("do", 0);
		ft_caps("cr", 0);
		ft_caps("sc", 0);
		ft_putstr(&str[all->pos_x + 1]);
		ft_caps("rc", 0);
	}
	else
	{
		ft_caps("sc", 0);
		ft_putstr(&str[all->pos_x]);
		ft_caps("rc", 0);
		ft_caps("nd", 0);
	}
}

void	ft_write_middle(t_all *all, char *str)
{
	int		g;
	int		y;

	y = 0;
	g = (((4 + all->pos_x) / all->winsize.x) + 1) * all->winsize.x;
	g -= (4 + all->pos_x);
	g--;
	if (g <= (int)ft_strlen(&str[all->pos_x + 1]))
	{
		ft_do_up(((ft_strlen(&str[all->pos_x + 1]) - g)\
			/ all->winsize.x) + 1);
		while (y++ < (all->pos_x + 4) % all->winsize.x)
			ft_caps("nd", 0);
	}
	ft_write_middle2(all, str);
	all->pos_x++;
	all->size++;
}

int		ft_count_line_histoy(char *line, t_all *all)
{
	int		i;
	int		nbr;
	int		size;

	i = 0;
	nbr = 0;
	size = 0;
	while (line[i])
	{
		if (size++ >= all->winsize.x || line[i] == '\n')
		{
			if (i >= all->pos_x)
				nbr++;
			size = 0;
		}
		i++;
	}
	return (nbr);
}

void	ft_replace_cursor(char *line, t_all *all)
{
	int		i;
	int		nbr;

	i = 0;
	nbr = ft_count_line_histoy(line, all);
	while (i++ < nbr)
	{
		ft_caps("up", 0);
	}
	i = 0;
	while (i++ < all->winsize.x)
		ft_caps("le", 0);
	i = 0;
	while (i++ < all->pos_x + 4)
		ft_caps("nd", 0);
}
