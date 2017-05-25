/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhervy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:14:31 by dhervy            #+#    #+#             */
/*   Updated: 2017/04/01 20:14:33 by dhervy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sh.h"

int		ft_token_dredir_left(char *line, int i)
{
	if (ft_isdigit(line[i]) && line[i - 1] == ' ')
		i++;
	if (line[i] == '<' && line[i + 1] == '<')
		return (DREDIG);
	else
		return (0);
}

int		ft_token_dredir_right(char *line, int i)
{
	if (ft_isdigit(line[i]) && line[i - 1] == ' ')
		i++;
	if (line[i] == '>' && line[i + 1] == '>')
		return (DREDID);
	else
		return (0);
}

int		ft_token_redir_left(char *line, int i)
{
	if (ft_isdigit(line[i]) && line[i - 1] == ' ')
		i++;
	if (line[i] == '<')
		return (REDIG);
	else
		return (0);
}

int		ft_token_redir_right(char *line, int i)
{
	if (ft_isdigit(line[i]) && line[i - 1] == ' ')
		i++;
	if (line[i] == '>')
		return (REDID);
	else
		return (0);
}

int		ft_token_agre(char *line, int i)
{
	if (ft_isdigit(line[i]) && line[i - 1] == ' ')
		i++;
	if (line[i] == '>' && line[i + 1] == '&')
		return (AGRE);
	else
		return (0);
}
