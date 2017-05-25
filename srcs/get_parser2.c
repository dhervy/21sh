/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_parser2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhervy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 19:50:15 by dhervy            #+#    #+#             */
/*   Updated: 2017/04/03 19:50:18 by dhervy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sh.h"

void	ft_push_commande(t_commande **commande, char *cmd, int token)
{
	t_commande	*new;
	t_commande	*tmp;

	new = (t_commande*)ft_memalloc(sizeof(t_commande) * 1);
	new->cmd = ft_strdup(cmd);
	free(cmd);
	new->token = token;
	if (!*commande)
	{
		*commande = new;
		new->next = NULL;
		new->right = NULL;
		new->prev = NULL;
	}
	else
	{
		tmp = *commande;
		while (tmp->next)
			tmp = tmp->next;
		new->prev = tmp;
		tmp->next = new;
		tmp->right = new;
		new->next = NULL;
	}
}

int		ft_get_dredirg(t_all *all, t_commande *comande)
{
	t_commande	*tmp;
	char		*str;

	tmp = comande;
	while (tmp)
	{
		if (tmp->token == DREDIG)
		{
			if (!ft_push_term(all))
				return (0);
			str = ft_strdupfree(tmp->next->cmd);
			tmp->next->cmd = ft_get_heredoc(all, str);
			free(str);
			if (tmp->next->cmd == NULL)
				return (0);
			if (!ft_reset_term(all))
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int		ft_check_token(char *line, int i)
{
	int		retour;

	retour = 0;
	if ((retour = ft_token_pipe(line, i)))
		return (retour);
	else if ((retour = ft_token_agre(line, i)))
		return (retour);
	else if ((retour = ft_token_dredir_left(line, i)))
		return (retour);
	else if ((retour = ft_token_dredir_right(line, i)))
		return (retour);
	else if ((retour = ft_token_redir_left(line, i)))
		return (retour);
	else if ((retour = ft_token_redir_right(line, i)))
		return (retour);
	else
		return (0);
}

void	ft_get_token2(t_all *all, t_commande **commande, char *line, int retour)
{
	if (retour == PIPE)
	{
		ft_push_commande(commande, ft_strdup("|"), PIPE);
		all->i++;
	}
	else if (retour == REDIG)
	{
		if (ft_isdigit(line[all->i]))
			ft_push_commande(commande, ft_strndup(&line[all->i++], 2), REDIG);
		else
			ft_push_commande(commande, ft_strndup(&line[all->i], 1), REDIG);
		all->i++;
	}
	else if (retour == REDID)
	{
		if (ft_isdigit(line[all->i]))
			ft_push_commande(commande, ft_strndup(&line[all->i++], 2), REDID);
		else
			ft_push_commande(commande, ft_strndup(&line[all->i], 1), REDID);
		all->i++;
	}
}

void	ft_get_token3(t_all *all, t_commande **commande, char *line, int retour)
{
	if (retour == DREDIG)
	{
		if (ft_isdigit(line[all->i]))
			ft_push_commande(commande, ft_strndup(&line[all->i++], 3), DREDIG);
		else
			ft_push_commande(commande, ft_strndup(&line[all->i], 2), DREDIG);
		all->i += 2;
	}
	else if (retour == DREDID)
	{
		if (ft_isdigit(line[all->i]))
			ft_push_commande(commande, ft_strndup(&line[all->i++], 3), DREDID);
		else
			ft_push_commande(commande, ft_strndup(&line[all->i], 2), DREDID);
		all->i += 2;
	}
	else if (retour == AGRE)
	{
		if (ft_isdigit(line[all->i]))
			ft_push_commande(commande, ft_strndup(&line[all->i++], 3), AGRE);
		else
			ft_push_commande(commande, ft_strndup(&line[all->i], 2), AGRE);
		all->i += 2;
	}
}
