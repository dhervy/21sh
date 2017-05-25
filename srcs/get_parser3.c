/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_parser3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhervy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 19:50:47 by dhervy            #+#    #+#             */
/*   Updated: 2017/04/03 19:50:49 by dhervy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sh.h"

int		ft_get_parser(char **multi_line)
{
	int			i;
	t_commande	*commande[ft_tablen(multi_line)];

	i = 0;
	while (i < ft_tablen(multi_line))
		commande[i++] = NULL;
	if (!ft_get_parser2(multi_line, commande))
		return (-1);
	ft_get_parser3(multi_line, commande);
	i = -1;
	while (++i < ft_tablen(multi_line))
	{
		ft_free_commande(commande[i]);
	}
	return (1);
}
