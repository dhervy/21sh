/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhervy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:13:44 by dhervy            #+#    #+#             */
/*   Updated: 2017/04/01 20:13:46 by dhervy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sh.h"

int		ft_check_only_env(char **str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (ft_strcmp(str[i], "env"))
			return (0);
		i++;
	}
	return (1);
}

int		ft_check_simple_quote(char *str, int i)
{
	if (str[i] == '\'')
	{
		i++;
		while (str[i] != '\'' && str[i])
			i++;
	}
	if (str[i] == '\'')
		i++;
	return (i);
}

char	*ft_push_var(char *str, t_all *all, int *i, int j)
{
	char	*result;
	char	*tmp;
	char	*var;
	int		index;

	var = ft_strndup(&str[j + 1], (*i - j) - 1);
	if (j > 0)
		result = ft_strndup(str, j);
	else
		result = (char *)ft_memalloc(sizeof(char) * 2);
	tmp = ft_searchenv(all->env, var);
	if (tmp)
		result = ft_strjoinfree(result, tmp, 0);
	index = ft_strlen(result);
	if (str[*i] != '\0')
	{
		tmp = ft_strdup(&str[*i]);
		result = ft_strjoinfree(result, tmp, 2);
	}
	*i = index;
	free(var);
	free(str);
	return (result);
}

void	ft_edit_var_env(t_all *all, t_commande *comande)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	if (comande->token == CMD)
	{
		str = ft_strdup(comande->cmd);
		while (str[i])
		{
			i = ft_check_simple_quote(str, i);
			if (str[i] == '$' && ft_isalnum(str[i + 1]))
			{
				j = i;
				while (str[i] != ' ' && str[i] != '\'' && str[i] != '\"' \
				&& str[i])
					i++;
				str = ft_push_var(str, all, &i, j);
			}
			else
				i++;
		}
		free(comande->cmd);
		comande->cmd = ft_strdupfree(str);
	}
}
