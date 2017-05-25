/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhervy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 19:47:58 by dhervy            #+#    #+#             */
/*   Updated: 2017/04/03 19:48:10 by dhervy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sh.h"

int		ft_get_multi_commande2(t_all *all, char *line, char **multi_line)
{
	if (line[all->i] == ';')
	{
		if (line[all->i + 1] == ';')
		{
			ft_tabfree(multi_line);
			return (0);
		}
		if (all->i > 0)
			multi_line[all->j++] = ft_strndup(&line[all->k], all->i - all->k);
		all->i++;
		all->k = all->i;
	}
	if (line[all->i] == '\'' || line[all->i] == '\"')
		all->i = ft_check_quote(line, all->i);
	if (line[all->i] != '\0')
		all->i++;
	return (1);
}
