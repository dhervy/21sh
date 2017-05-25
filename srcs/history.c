/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhervy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/17 20:12:49 by dhervy            #+#    #+#             */
/*   Updated: 2017/04/01 20:06:44 by dhervy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sh.h"

t_history	*ft_init_history(t_history *new_history)
{
	new_history = (t_history*)ft_memalloc(sizeof(t_history));
	new_history->value = NULL;
	new_history->size = 1;
	new_history->prev = NULL;
	new_history->next = NULL;
	return (new_history);
}

void		ft_add_history(t_history *new_history, t_history **history)
{
	t_history	*tmp;

	tmp = *history;
	if (tmp)
	{
		new_history->next = tmp;
		tmp->prev = new_history;
		*history = new_history;
	}
	else
		*history = new_history;
}

t_history	*ft_search_history_up(t_history **start, char *line, int pos)
{
	t_history	*tmp;

	tmp = *start;
	while (42)
	{
		tmp = tmp->next;
		if (tmp == NULL)
			return (NULL);
		if (!ft_strncmp(tmp->value, line, pos))
		{
			*start = tmp;
			return (tmp);
		}
	}
	return (NULL);
}

t_history	*ft_search_history_down(t_history **start, char *line, int pos)
{
	t_history	*tmp;

	tmp = *start;
	while (42)
	{
		tmp = tmp->prev;
		if (!tmp || tmp->value == NULL)
			return (NULL);
		if (!ft_strncmp(tmp->value, line, pos))
		{
			*start = tmp;
			return (tmp);
		}
	}
	return (NULL);
}
