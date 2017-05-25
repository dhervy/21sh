/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhervy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 19:12:09 by dhervy            #+#    #+#             */
/*   Updated: 2017/04/01 20:05:43 by dhervy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sh.h"

int		ft_envu(t_all *all, char **str, int i)
{
	int		j;

	j = 0;
	while (str[i][j] != '=' && str[i][j] != '\0')
		j++;
	if (str[i][j] == '=')
	{
		ft_putstr("env: unsetenv ");
		ft_putstr(str[i]);
		ft_putstr(": Invalid argument\n");
		i = ft_tablen(str);
	}
	else
		all->envcpy = ft_removenv(all->envcpy, str[i]);
	return (i + 1);
}

void	ft_envi(t_all *all)
{
	int		j;

	j = 0;
	while (all->envcpy[j])
	{
		ft_bzero(all->envcpy[j], ft_strlen(all->envcpy[j]));
		free(all->envcpy[j]);
		j++;
	}
	free(all->envcpy);
	all->envcpy = (char**)ft_memalloc(sizeof(char*) * 2);
}

int		ft_env(t_all *all, char **str, int i)
{
	int		j;
	char	*line;

	j = 0;
	if (!ft_strcmp(str[i], "env") && str[i + 1][0] != '-')
		return (i + 1);
	while (str[i][j] != '=' && j < (int)ft_strlen(str[i]))
		j++;
	if (j < (int)ft_strlen(str[i]))
	{
		line = ft_strndup(str[i], j);
		all->envcpy = ft_addenv(all->envcpy, line, &str[i][j + 1]);
		free(line);
	}
	else
	{
		ft_exec(all, &str[i], all->envcpy);
		i = ft_tablen(str);
	}
	return (i + 1);
}
