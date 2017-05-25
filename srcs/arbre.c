/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arbre.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhervy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:13:01 by dhervy            #+#    #+#             */
/*   Updated: 2017/04/01 20:13:05 by dhervy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sh.h"

int		ft_clean_commande(t_commande *commande)
{
	t_commande	*tmp;
	int			i;

	i = 0;
	tmp = commande;
	while (tmp)
	{
		while (commande->cmd[i])
		{
			if (commande->cmd[i] != ' ' && commande->cmd != '\0')
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

t_arbre	*ft_init_arbre(t_arbre *new_arbre)
{
	new_arbre = (t_arbre*)ft_memalloc(sizeof(t_arbre));
	new_arbre->cmd = NULL;
	new_arbre->token = 0;
	new_arbre->left = NULL;
	new_arbre->right = NULL;
	new_arbre->top = NULL;
	return (new_arbre);
}

void	ft_create_arbre(t_arbre **arbre, t_arbre *top, t_commande **commande)
{
	t_arbre		*new_arbre;
	t_commande	*tmp;
	char		*str;

	new_arbre = NULL;
	tmp = *commande;
	new_arbre = ft_init_arbre(new_arbre);
	*arbre = new_arbre;
	str = NULL;
	if (ft_create_arbre_pipe(arbre, top, commande, new_arbre))
		return ;
	if (ft_create_arbre_redi(arbre, top, commande, new_arbre))
		return ;
	while (tmp)
	{
		if (tmp->token == CMD)
		{
			if (!str)
				str = ft_strdup(tmp->cmd);
			else
				str = ft_strjoinfree(str, tmp->cmd, 0);
		}
		tmp = tmp->next;
	}
	ft_create_arbre_cmd(new_arbre, top, str);
}
