/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envcopy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhervy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/06 17:29:57 by dhervy            #+#    #+#             */
/*   Updated: 2017/04/01 20:05:54 by dhervy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sh.h"

char	**ft_envcopy(char **env, char *str)
{
	int		i;
	char	**new;

	i = 0;
	new = NULL;
	i = ft_tablen(env);
	new = (char**)ft_memalloc(sizeof(char*) * (i + 2));
	i = 0;
	while (env[i])
	{
		new[i] = (char*)ft_memalloc(sizeof(char) * (ft_strlen(env[i]) + 1));
		ft_strcpy(new[i], env[i]);
		i++;
	}
	new[i] = (char*)ft_memalloc(sizeof(char) * (ft_strlen(str) + 1));
	ft_strcpy(new[i], str);
	ft_tabfree(env);
	return (new);
}

char	**ft_envdelet(char **env, int sup)
{
	char	**new;
	int		i;
	int		j;

	new = NULL;
	i = 0;
	j = 0;
	new = (char**)ft_memalloc(sizeof(char*) * (ft_tablen(env) + 1));
	while (env[i])
	{
		if (i == sup)
			i++;
		else
		{
			new[j] = (char*)ft_memalloc(sizeof(char) * (ft_strlen(env[i]) + 1));
			ft_strcpy(new[j], env[i]);
			i++;
			j++;
		}
	}
	ft_tabfree(env);
	return (new);
}
