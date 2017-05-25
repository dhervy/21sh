/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhervy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 21:12:05 by dhervy            #+#    #+#             */
/*   Updated: 2017/04/01 20:05:48 by dhervy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sh.h"

int		ft_envshell3(t_all *all, char **str, int i, int *arg)
{
	if (arg[1] == 1)
	{
		arg[1] = 0;
		arg[0] = 0;
		ft_envi(all);
		i++;
	}
	else if (arg[0] == 1)
	{
		arg[0] = 0;
		i = ft_envu(all, str, i + 1);
	}
	return (i);
}

void	ft_initenvshell(t_all *all, char **str)
{
	int		i;
	int		j;
	int		arg[2];

	i = 0;
	j = 1;
	arg[0] = 0;
	arg[1] = 0;
	if (all->envcpy)
		ft_tabfree(all->envcpy);
	all->envcpy = ft_tabdup(all->env, ft_tablen(all->env) + 1);
	ft_envshell2(str, i, j, arg);
}

int		ft_envshell4(char **str, int i, int j, int *arg)
{
	arg[1] = 0;
	arg[0] = 0;
	ft_putstr("env: illegal option -- ");
	ft_putchar(str[i][j]);
	ft_putstr("\nusage: env [-iu] [Variable]\n");
	i = ft_tablen(str);
	return (i);
}

int		ft_envshell5(char **str, int i, int j, int *arg)
{
	while (str[i][j])
	{
		if (str[i][j] == 'i')
			arg[1] = 1;
		else if (str[i][j] == 'u')
			arg[0] = 1;
		else
		{
			i = ft_envshell4(str, i, j, arg);
			break ;
		}
		j++;
		if (!str[i][j] && str[i + 1][0] == '-')
		{
			i++;
			j = 1;
		}
	}
	return (i);
}

void	ft_envshell2(char **str, int i, int j, int *arg)
{
	t_all *all;

	all = ft_singleton();
	while (i < ft_tablen(str))
	{
		j = 1;
		if (!ft_strcmp(str[i], "env") && str[i + 1][0] == '-')
		{
			i++;
			i = ft_envshell5(str, i, j, arg);
			i = ft_envshell3(all, str, i, arg);
		}
		else
			i = ft_env(all, str, i);
	}
}
