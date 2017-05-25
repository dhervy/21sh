/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhervy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 13:06:25 by dhervy            #+#    #+#             */
/*   Updated: 2017/04/05 15:57:52 by dhervy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sh.h"

void	ft_move_char_left(char *str, int i)
{
	int		j;

	j = i + 1;
	while (str[j])
	{
		str[i] = str[j];
		i++;
		j++;
	}
	str[i] = '\0';
}

char	**ft_strsplit_quote2(char **str, char **tableau)
{
	if ((*str)[0] == '\0')
	{
		free(*str);
		*str = ft_strdup(" ");
	}
	tableau = ft_strsplit(*str, '\t');
	return (tableau);
}

char	**ft_strsplit_quote(char **str)
{
	t_all	*all;
	char	**tableau;

	tableau = NULL;
	all = ft_singleton();
	ft_init_ijk();
	while ((*str)[all->i])
	{
		while ((*str)[all->i] && (*str)[all->i] != ' ')
		{
			if ((*str)[all->i] == '\'' || (*str)[all->i] == '\"')
			{
				all->j = all->i;
				all->i = ft_check_quote(*str, all->i) + 1;
				ft_move_char_left(*str, all->j);
				ft_move_char_left(*str, all->i - 2);
				all->i = all->i - 2;
			}
			else
				all->i++;
		}
		if ((*str)[all->i])
			(*str)[all->i++] = '\t';
	}
	return (ft_strsplit_quote2(str, tableau));
}

int		ft_exec_bultin(t_all *all, char **cmd)
{
	if (!ft_strcmp(cmd[0], "exit"))
	{
		ft_exitshell(cmd);
		return (1);
	}
	if (!ft_strcmp(cmd[0], "echo"))
	{
		ft_echoshell(cmd, 0, 0);
		return (1);
	}
	if (!ft_strcmp(cmd[0], "cd"))
	{
		ft_cdshell(all, cmd);
		return (1);
	}
	if (!ft_strcmp(cmd[0], "env") || !ft_strcmp(cmd[0], "setenv")\
		|| !ft_strcmp(cmd[0], "unsetenv"))
	{
		ft_envshell(all, cmd);
		return (1);
	}
	return (0);
}
