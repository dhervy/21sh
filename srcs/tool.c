/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhervy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 14:59:18 by dhervy            #+#    #+#             */
/*   Updated: 2017/04/02 14:59:27 by dhervy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sh.h"

t_all	*ft_singleton(void)
{
	static t_all	all;
	static int		init = 0;

	if (!init)
	{
		ft_bzero(&all, sizeof(t_all));
		init = 1;
	}
	return (&all);
}

void	sigfunc(int sig)
{
	t_all *all;

	all = ft_singleton();
	if (sig == SIGINT)
	{
		ft_putprompt(all);
		all->prompt = 1;
	}
}

void	ft_putprompt(t_all *all)
{
	ft_putchar('\n');
	ft_putcolor("21sh{", RED);
	ft_putstr("\033[4m");
	ft_putcolor(all->pwd, GREEN);
	ft_putcolor("}", RED);
	ft_putchar('\n');
	ft_putstr(" -> ");
}

int		ft_putc(int c)
{
	return (write(1, &c, 1));
}

void	ft_caps(char *cmd, int fd)
{
	char	*str;

	str = NULL;
	if ((str = tgetstr(cmd, NULL)))
		tputs(str, fd, ft_putc);
}
