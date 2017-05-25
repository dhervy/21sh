/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhervy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:13:37 by dhervy            #+#    #+#             */
/*   Updated: 2017/04/01 20:13:39 by dhervy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sh.h"

void	ft_echoshell(char **str, int n, int i)
{
	if (!ft_strcmp(str[0], "echo"))
	{
		if (ft_tablen(str) == 1)
		{
			ft_putchar('\n');
			return ;
		}
		if (str[1][0] == '-')
		{
			if (str[1][1] == 'n')
				n = 1;
			else
				ft_putchar(str[1][1]);
		}
		i = (n == 0 ? 1 : 2);
		while (str[i])
		{
			ft_putstr(str[i]);
			i++;
			if (str[i])
				ft_putchar(' ');
		}
		if (n == 0)
			ft_putchar('\n');
	}
}
