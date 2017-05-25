/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhervy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:14:18 by dhervy            #+#    #+#             */
/*   Updated: 2017/04/05 15:59:48 by dhervy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sh.h"

int		ft_get_heredoc3(char *cmp, char **line, char **str, unsigned long buf)
{
	t_all *all;

	all = ft_singleton();
	if (!ft_strcmp(cmp, *line) || (all->size <= 1 && buf == CTRLD))
	{
		ft_putchar('\n');
		if (*line)
			free(*line);
		return (1);
	}
	else
		ft_putchar('\n');
	if (!*str)
		*str = ft_strdup(*line);
	else
	{
		*str = ft_strjoinfree(*str, "\n", 0);
		*str = ft_strjoinfree(*str, *line, 0);
	}
	free(*line);
	all->size = 1;
	all->pos_x = 0;
	return (0);
}

int		ft_get_heredoc2(t_all *all, unsigned long buf, char **line)
{
	buf = 0;
	read(0, (char*)&buf, 8);
	if (all->prompt == 1)
	{
		free(*line);
		all->size = 1;
		all->pos_x = 0;
		return (0);
	}
	all = ft_get_winsize(all);
	if (!ft_get_key(buf, all, line, NULL) && ft_isprint(buf))
	{
		*line = (char*)ft_realloc(*line, all->size + 1, buf, all);
		if (all->pos_x == all->size - 1)
		{
			ft_putchar(buf);
			all->pos_x++;
			all->size++;
		}
		else
			ft_write_middle(all, *line);
	}
	return (buf);
}

char	*ft_get_heredoc(t_all *all, char *cmp)
{
	unsigned long	buf;
	char			*line;
	char			*str;

	str = NULL;
	buf = 0;
	ft_init_size_posx();
	while (42)
	{
		ft_putstr(" >> ");
		line = (char*)ft_memalloc(sizeof(char) * 1);
		while (42)
		{
			if (!(buf = ft_get_heredoc2(all, buf, &line)))
				return (NULL);
			if (buf == 10 || (all->size <= 1 && buf == CTRLD))
			{
				ft_putstr(&line[all->pos_x]);
				break ;
			}
		}
		if (ft_get_heredoc3(cmp, &line, &str, buf))
			return (str);
	}
	return (NULL);
}
