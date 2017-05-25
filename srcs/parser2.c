/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhervy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:15:01 by dhervy            #+#    #+#             */
/*   Updated: 2017/04/03 18:15:09 by dhervy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sh.h"

int		ft_check_point_virgule(char *line)
{
	if (line[0] == '|' && (line[1] == ' ' || line[1] == '\0'))
		return (1);
	return (0);
}

int		ft_check_pipe(char *line)
{
	if (line[0] == '|' && (line[1] == ' ' || line[1] == '\0'))
		return (1);
	return (0);
}

int		ft_check_quote(char *line, int i)
{
	int		j;

	j = i;
	i++;
	while (line[i] != line[j] && line[i])
		i++;
	return (i);
}

char	*ft_delete_space(char *line)
{
	int i;
	int j;
	int k;

	j = 0;
	k = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			i = ft_check_quote(line, i);
		if (line[i] == ' ' && line[i + 1] == ' ')
		{
			j = i;
			while (line[j])
			{
				line[j] = line[j + 1];
				j++;
			}
		}
		else
			i++;
	}
	return (line);
}

int		ft_free_line_tab(char *line, char **multi_line)
{
	if (line)
		free(line);
	if (multi_line)
		ft_tabfree(multi_line);
	return (-1);
}
