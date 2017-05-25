/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhervy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 21:15:41 by dhervy            #+#    #+#             */
/*   Updated: 2017/04/03 21:15:49 by dhervy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sh.h"

int		ft_check_line(char *line)
{
	int		i;
	int		quote;

	i = 0;
	quote = 0;
	while (line[i])
	{
		if (line[i] == '\'')
		{
			if (quote == 0)
				quote = 1;
			else if (quote == 1)
				quote = 0;
		}
		if (line[i] == '\"')
		{
			if (quote == 0)
				quote = 2;
			else if (quote == 2)
				quote = 0;
		}
		i++;
	}
	return (quote);
}
