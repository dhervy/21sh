/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhervy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 17:07:37 by dhervy            #+#    #+#             */
/*   Updated: 2017/04/01 20:06:49 by dhervy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sh.h"

int		ft_print_error(char *str)
{
	ft_putstr_fd("21sh: parse error near `", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("'", 2);
	return (-1);
}

int		ft_lexer_return(t_commande *tmp)
{
	if (tmp->next->token == PIPE)
		return (ft_print_error("|"));
	else if (tmp->next->token == REDID)
		return (ft_print_error(">"));
	else if (tmp->next->token == REDIG)
		return (ft_print_error("<"));
	else if (tmp->next->token == DREDID)
		return (ft_print_error(">>"));
	else if (tmp->next->token == DREDIG)
		return (ft_print_error("<<"));
	else if (tmp->next->token == AGRE)
		return (ft_print_error(">&"));
	return (-1);
}

int		ft_lexer(t_commande **commande)
{
	t_commande	*tmp;

	tmp = *commande;
	if (tmp->token == PIPE)
		return (ft_print_error("|"));
	while (tmp)
	{
		if (tmp->token == REDID || tmp->token == REDIG || tmp->token == DREDIG \
			|| tmp->token == DREDID || tmp->token == AGRE)
		{
			if (!tmp->next)
				return (ft_print_error("\\n"));
			else if (tmp->next && tmp->next->token != CMD)
				return (ft_lexer_return(tmp));
		}
		if (tmp->token == PIPE)
		{
			if (tmp->next == NULL)
				return (ft_print_error("|"));
			if (tmp->next->token == PIPE || tmp->prev->token == PIPE)
				return (ft_print_error("|"));
		}
		tmp = tmp->next;
	}
	return (1);
}
