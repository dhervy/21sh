/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_term.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhervy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/17 17:07:27 by dhervy            #+#    #+#             */
/*   Updated: 2017/04/01 20:06:21 by dhervy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sh.h"

t_all	*ft_get_winsize(t_all *all)
{
	struct winsize	w;

	ioctl(0, TIOCGWINSZ, &w);
	all->winsize.y = w.ws_row;
	all->winsize.x = w.ws_col;
	return (all);
}

int		ft_reset_term(t_all *all)
{
	if (tgetent(NULL, (all->name_term = getenv("TERM"))) < 1)
	{
		ft_putstr("Error : Variable TERM not Found\n");
		return (0);
	}
	tcsetattr(0, TCSADRAIN, &all->termcpy);
	return (1);
}

int		ft_push_term(t_all *all)
{
	if (tgetent(NULL, (all->name_term = getenv("TERM"))) < 1)
	{
		ft_putstr("Error : Variable TERM not Found\n");
		return (0);
	}
	tcsetattr(0, TCSADRAIN, &all->term);
	return (1);
}

int		ft_init_term(t_all *all)
{
	if (tgetent(NULL, (all->name_term = getenv("TERM"))) < 1)
	{
		ft_putstr("Error : Variable TERM not Found\n");
		return (0);
	}
	if (tcgetattr(0, &all->term) == -1)
	{
		ft_putstr("Error : Variable TERM\n");
		return (0);
	}
	if (tcgetattr(0, &all->termcpy) == -1)
	{
		ft_putstr("Error : Variable TERM\n");
		return (0);
	}
	all->term.c_lflag &= ~(ICANON | ECHO);
	all->term.c_cc[VMIN] = 1;
	all->term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSADRAIN, &all->term);
	return (1);
}
