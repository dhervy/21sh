/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplet4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhervy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 21:59:29 by dhervy            #+#    #+#             */
/*   Updated: 2017/04/01 21:59:40 by dhervy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sh.h"

void	ft_auto_move_cursor(t_auto **lsauto, t_all *all, int columnlist)
{
	int		nbr;
	int		i;

	i = 0;
	nbr = ft_auto_get_nbrline(lsauto, columnlist);
	while (i++ < nbr)
	{
		ft_caps("up", 0);
	}
	i = 0;
	while (i++ < all->column)
		ft_caps("le", 0);
	i = 0;
	while (i++ < all->pos_x + 4)
		ft_caps("nd", 0);
}

void	ft_auto_print_color(char *str, int select)
{
	if (select == 1)
	{
		ft_putstr("\033[7m");
		ft_putstr(str);
		ft_putstr("\033[0m");
	}
	else
	{
		ft_putstr("\033[1m");
		ft_putcolor(str, RED);
	}
}

void	ft_print_auto(t_auto **lsauto, t_all *all, int i)
{
	t_auto	*tmp;
	int		sizemax;
	int		columnlist;

	tmp = *lsauto;
	i = 0;
	ft_caps("cd", 0);
	ft_caps("do", 0);
	ft_count_column(all);
	sizemax = ft_auto_sizemax(lsauto);
	columnlist = (all->column / (sizemax + 1));
	while (tmp)
	{
		if (i == columnlist)
		{
			ft_putchar('\n');
			i = 0;
		}
		ft_auto_print_color(tmp->value, tmp->select);
		if (i != columnlist)
			ft_putspace(sizemax - ft_strlen(tmp->value) + 1);
		i++;
		tmp = tmp->next;
	}
	ft_auto_move_cursor(lsauto, all, columnlist);
}

void	ft_auto_move_right(t_auto **lsauto)
{
	t_auto	*tmp;

	tmp = *lsauto;
	while (tmp && tmp->select == 0)
		tmp = tmp->next;
	tmp->select = 0;
	if (tmp->next != NULL)
		tmp->next->select = 1;
	else
		(*lsauto)->select = 1;
}
