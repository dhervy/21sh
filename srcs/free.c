/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhervy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:14:05 by dhervy            #+#    #+#             */
/*   Updated: 2017/04/01 20:14:07 by dhervy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sh.h"

void	ft_free_commande(t_commande *commande)
{
	t_commande	*tmp;
	t_commande	*tmp2;

	tmp = commande;
	while (tmp)
	{
		tmp2 = tmp;
		tmp = tmp->right;
		tmp2->token = 0;
		free(tmp2->cmd);
		tmp2->cmd = NULL;
		tmp2->prev = NULL;
		tmp2->next = NULL;
		tmp2->right = NULL;
		free(tmp2);
	}
}

void	ft_free_arbre(t_arbre **arbre)
{
	t_arbre	*tmp;

	tmp = *arbre;
	if (tmp->cmd)
		free(tmp->cmd);
	tmp->cmd = NULL;
	if (tmp->left)
		ft_free_arbre(&tmp->left);
	if (tmp->right)
		ft_free_arbre(&tmp->right);
	free(tmp);
}
