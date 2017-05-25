/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove_cursor3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhervy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 15:18:33 by dhervy            #+#    #+#             */
/*   Updated: 2017/04/02 15:18:41 by dhervy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sh.h"

int		ft_check_move_right(t_all *all, char *line)
{
	int		i;

	i = all->pos_x - 1;
	while (i > 0 && line[i] != '\n')
		i--;
	if (i == 0)
	{
		if ((4 + all->pos_x) % all->winsize.x == 0)
			return (1);
		else
			return (0);
	}
	else
	{
		if ((all->pos_x - i) % all->winsize.x == 0)
			return (1);
		else
			return (0);
	}
}

int		ft_move_right_quote(t_all *all, char *line)
{
	int		i;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\0')
	{
		if ((4 + all->pos_x) % all->winsize.x == 0)
			return (1);
		else
			return (0);
	}
	else
	{
		if (line[all->pos_x - 1] == '\n')
			return (1);
		else if (ft_check_move_right(all, line))
			return (1);
		else
			return (0);
	}
}

int		ft_move_right(t_all *all, char *line)
{
	all->pos_x++;
	if (ft_move_right_quote(all, line))
	{
		ft_caps("do", 0);
	}
	else
		ft_caps("nd", 0);
	return (1);
}

void	ft_delete(t_all *all, char **line)
{
	*line = ft_realloc(*line, all->size - 1, 'A', all);
	ft_caps("le", 0);
	ft_caps("sc", 0);
	ft_caps("cd", 0);
	ft_putstr(&(*line)[all->pos_x - 1]);
	ft_caps("rc", 0);
	all->pos_x--;
	all->size--;
}
