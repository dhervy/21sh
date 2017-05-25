/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhervy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 20:13:32 by dhervy            #+#    #+#             */
/*   Updated: 2017/04/03 20:13:39 by dhervy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sh.h"

void	ft_get_key5(t_all *all, char **line, unsigned long buf, \
	t_history **start)
{
	t_history	*tmp;

	if (buf == UP && start != NULL)
	{
		tmp = ft_search_history_up(start, *line, all->pos_x);
		if (tmp != NULL && tmp->value != NULL)
		{
			all->size = tmp->size;
			free(*line);
			*line = ft_strdup(tmp->value);
			ft_caps("cd", 0);
			if (tmp->value)
				ft_putstr(&(*line)[all->pos_x]);
			ft_replace_cursor(*line, all);
		}
	}
}

void	ft_get_key6(t_all *all, char **line, unsigned long buf, \
	t_history **start)
{
	t_history	*tmp;

	if (buf == DOWN && start != NULL)
	{
		tmp = ft_search_history_down(start, *line, all->pos_x);
		if (tmp != NULL)
		{
			all->size = tmp->size;
			free(*line);
			if (tmp->value)
				*line = ft_strdup(tmp->value);
			else
			{
				*line = ft_strndup(*line, all->pos_x);
			}
			ft_caps("sc", 0);
			ft_caps("cd", 0);
			if (tmp->value)
				ft_putstr(&(*line)[all->pos_x]);
			ft_caps("rc", 0);
		}
	}
}

void	ft_get_key7bis(t_all *all, char c)
{
	ft_putchar(c);
	all->pos_x++;
	all->size++;
}

void	ft_get_key7(t_all *all, char **line, unsigned long buf, int i)
{
	char	*str;

	if (buf == TAB)
	{
		if ((*line)[all->pos_x - 1] != '\0')
		{
			str = ft_auto_complet(line, all);
			if (str == NULL)
				return ;
			while (i < (int)ft_strlen(str))
			{
				*line = (char*)ft_realloc(*line, all->size + 1, str[i], all);
				if (all->pos_x == all->size - 1)
				{
					ft_get_key7bis(all, str[i]);
				}
				else
					ft_write_middle(all, *line);
				i++;
			}
			free(str);
		}
	}
}

int		ft_get_key(unsigned long buf, t_all *all, char **line, \
	t_history **start)
{
	ft_get_key2(all, line, buf);
	ft_get_key3(all, line, buf);
	ft_get_key4(all, line, buf);
	ft_get_key5(all, line, buf, start);
	ft_get_key6(all, line, buf, start);
	ft_get_key7(all, line, buf, 0);
	return (0);
}
