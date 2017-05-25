/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhervy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/17 18:15:41 by dhervy            #+#    #+#             */
/*   Updated: 2017/04/01 20:06:26 by dhervy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sh.h"

void		ft_get_line2bis(t_all *all, t_history **new_history, char **line)
{
	if ((*new_history)->value)
	{
		free((*new_history)->value);
		(*new_history)->value = NULL;
	}
	(*new_history)->size = 1;
	if (*line)
		free(*line);
	all->size = 1;
	all->pos_x = 0;
	*line = (char*)ft_memalloc(sizeof(char) * 1);
	all->prompt = 0;
}

int			ft_get_line2(t_all *all, t_history **new_history, \
	char **line, t_history **start)
{
	unsigned long	buf;

	buf = 0;
	read(0, (char*)&buf, 8);
	if (all->prompt == 1)
		ft_get_line2bis(all, new_history, line);
	all = ft_get_winsize(all);
	if (!ft_get_key(buf, all, line, start) && ft_isprint(buf))
	{
		*line = (char*)ft_realloc(*line, all->size + 1, buf, all);
		if (all->pos_x == all->size - 1)
			ft_get_key7bis(all, buf);
		else
			ft_write_middle(all, *line);
	}
	if (buf == CTRLD && all->size <= 1 && (*new_history)->size <= 1)
		exit(0);
	if (buf == ENTER)
	{
		ft_putstr(&(*line)[all->pos_x]);
		return (0);
	}
	return (1);
}

void		ft_get_line3(t_all *all, t_history **new_history, char **line)
{
	if (!(*new_history)->value)
	{
		(*new_history)->value = ft_strdup(*line);
		(*new_history)->size = all->size;
	}
	else
	{
		(*new_history)->value = ft_strjoinfree((*new_history)->value, "\n", 0);
		(*new_history)->value = ft_strjoinfree((*new_history)->value, *line, 0);
		(*new_history)->size = (*new_history)->size + all->size;
	}
	if (*line)
		free(*line);
	all->size = 1;
	all->pos_x = 0;
}

t_history	*ft_get_line4(t_all *all, t_history *new_history)
{
	all->pos_x = 0;
	all->size = 1;
	new_history = NULL;
	new_history = ft_init_history(new_history);
	return (new_history);
}

char		*ft_get_line(t_all *all, t_history **history)
{
	t_history		*new_history;
	t_history		*start;
	char			*line;

	new_history = NULL;
	new_history = ft_get_line4(all, new_history);
	ft_add_history(new_history, history);
	start = *history;
	while (42)
	{
		line = (char*)ft_memalloc(sizeof(char) * 1);
		while (42)
			if (!ft_get_line2(all, &new_history, &line, &start))
				break ;
		ft_get_line3(all, &new_history, &line);
		if (!ft_check_line(new_history->value))
		{
			if (!ft_reset_term(all))
				return (0);
			return (ft_strdup(new_history->value));
		}
		else
			ft_putstr("\n -> ");
	}
	return (NULL);
}
