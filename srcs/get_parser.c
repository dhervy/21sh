/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhervy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:14:13 by dhervy            #+#    #+#             */
/*   Updated: 2017/04/01 20:14:15 by dhervy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sh.h"

int		ft_get_token4(t_all *all, t_commande **commande, char *line, int retour)
{
	while (ft_isspace(line[all->i]))
		all->i++;
	if (line[all->i] == '\0')
		return (0);
	all->j = all->i;
	while (!(retour = ft_check_token(line, all->i)) && \
		!ft_isspace(line[all->i]) && line[all->i] != '\0')
	{
		if (line[all->i] == '\'' || line[all->i] == '\"')
			all->i = ft_check_quote(line, all->i);
		if (retour == 0)
			all->k = 1;
		all->i++;
	}
	if (line[all->i] == '\0')
		ft_push_commande(commande, ft_strdup(&line[all->j]), CMD);
	else if (line[all->i] == ' ' || all->k == 1)
	{
		ft_push_commande(commande, ft_strndup(&line[all->j], \
			all->i - all->j), CMD);
		all->k = 0;
		if (line[all->i] == ' ')
			all->i++;
	}
	return (1);
}

int		ft_get_token5(t_all *all, t_commande **commande, char *line, int retour)
{
	if (all->k)
	{
		ft_push_commande(commande, ft_strndup(&line[all->j], \
			all->i - all->j), CMD);
		all->k = 0;
	}
	if (retour == PIPE || retour == REDIG || retour == REDID)
		ft_get_token2(all, commande, line, retour);
	else if (retour == AGRE || retour == DREDID || retour == DREDIG)
		ft_get_token3(all, commande, line, retour);
	if (retour != PIPE)
		if (!ft_get_token4(all, commande, line, retour))
			return (0);
	return (1);
}

void	ft_get_token(t_all *all, t_commande **commande, char *line)
{
	int		retour;

	retour = 0;
	ft_init_ijk();
	while (line[all->i])
	{
		while (ft_isspace(line[all->i]) && line[all->i] != '\0')
			all->i++;
		all->j = all->i;
		while (!(retour = ft_check_token(line, all->i)) && line[all->i] != '\0')
		{
			if (line[all->i] == '\'' || line[all->i] == '\"')
				all->i = ft_check_quote(line, all->i);
			all->i++;
			all->k = 1;
		}
		if (retour)
		{
			if (!ft_get_token5(all, commande, line, retour))
				return ;
		}
		else if (line[all->i] == '\0')
			ft_push_commande(commande, ft_strdup(&line[all->j]), CMD);
	}
}

int		ft_get_parser2(char **multi_line, t_commande **commande)
{
	int		i;

	i = -1;
	while (++i < ft_tablen(multi_line))
		ft_get_token(ft_singleton(), &commande[i], multi_line[i]);
	i = -1;
	while (++i < ft_tablen(multi_line))
	{
		if (ft_lexer(&commande[i]) == -1)
		{
			i = -1;
			while (++i < ft_tablen(multi_line))
			{
				ft_free_commande(commande[i]);
			}
			ft_tabfree(multi_line);
			return (0);
		}
	}
	return (1);
}

void	ft_get_parser3(char **multi_line, t_commande **commande)
{
	int			i;
	t_commande	*tmp;

	i = -1;
	while (++i < ft_tablen(multi_line))
	{
		tmp = commande[i];
		while (tmp)
		{
			ft_edit_var_env(ft_singleton(), commande[i]);
			tmp = tmp->next;
		}
		if (ft_get_dredirg(ft_singleton(), commande[i]))
		{
			ft_get_arbre(commande[i]);
		}
	}
}
