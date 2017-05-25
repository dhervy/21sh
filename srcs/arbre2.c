/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arbre2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhervy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:54:21 by dhervy            #+#    #+#             */
/*   Updated: 2017/04/01 20:54:35 by dhervy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sh.h"

int		ft_create_arbre_pipe(t_arbre **arbre, t_arbre *top, \
	t_commande **commande, t_arbre *new_arbre)
{
	t_commande	*tmp;
	t_commande	*tmp2;

	tmp = *commande;
	while (tmp)
	{
		if (tmp->token == PIPE)
		{
			new_arbre->cmd = ft_strdup("|");
			new_arbre->token = PIPE;
			new_arbre->top = top;
			tmp->next->prev = NULL;
			tmp->prev->next = NULL;
			tmp2 = tmp;
			tmp = tmp->next;
			ft_create_arbre(&new_arbre->left, *arbre, commande);
			ft_create_arbre(&new_arbre->right, *arbre, &tmp);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	ft_create_arbre_redi2(t_arbre *new_arbre, t_arbre *top, \
	t_commande *tmp, t_commande **commande)
{
	new_arbre->cmd = ft_strdup(tmp->cmd);
	new_arbre->token = tmp->token;
	new_arbre->top = top;
	if (tmp->next->next)
	{
		tmp->next->next->prev = tmp->prev;
		if (!tmp->prev)
			*commande = tmp->next->next;
	}
	if (tmp->prev)
	{
		if (tmp->next->next)
			tmp->prev->next = tmp->next->next;
		else
			tmp->prev->next = NULL;
	}
}

int		ft_create_arbre_redi(t_arbre **arbre, t_arbre *top, \
	t_commande **commande, t_arbre *new_arbre)
{
	t_commande	*tmp;
	t_commande	*tmp2;

	tmp = *commande;
	while (tmp->next)
		tmp = tmp->next;
	while (tmp)
	{
		if (tmp->token != PIPE && tmp->token != CMD)
		{
			ft_create_arbre_redi2(new_arbre, top, tmp, commande);
			tmp2 = tmp;
			tmp = tmp->next;
			tmp->next = NULL;
			tmp->prev = NULL;
			ft_create_arbre(&new_arbre->left, *arbre, commande);
			ft_create_arbre(&new_arbre->right, *arbre, &tmp);
			return (1);
		}
		tmp = tmp->prev;
	}
	return (0);
}

void	ft_create_arbre_cmd(t_arbre *new_arbre, t_arbre *top, char *str)
{
	new_arbre->cmd = ft_strdupfree(str);
	new_arbre->token = CMD;
	new_arbre->top = top;
}
