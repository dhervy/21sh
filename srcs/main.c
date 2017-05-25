/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhervy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/17 17:06:29 by dhervy            #+#    #+#             */
/*   Updated: 2017/04/01 20:06:55 by dhervy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sh.h"

void	ft_put_header(void)
{
	ft_putstr(LINE1);
	ft_putstr(LINE1B);
	ft_putstr(LINE2);
	ft_putstr(LINE2B);
	ft_putstr(LINE3);
	ft_putstr(LINE3B);
	ft_putstr(LINE4);
	ft_putstr(LINE4B);
	ft_putstr(LINE5);
	ft_putstr(LINE5B);
	ft_putstr(LINE6);
	ft_putstr(LINE6B);
	ft_putstr(LINE7);
	ft_putstr(LINE7B);
	ft_putstr(LINE8);
	ft_putstr(LINE8B);
	ft_putstr(LINE9);
	ft_putstr(LINE9B);
	ft_putstr(LINE10);
	ft_putstr(LINE10B);
}

void	ft_goto(int x, int y)
{
	ft_putstr("\033[");
	ft_putnbr(y);
	ft_putchar(';');
	ft_putnbr(x);
	ft_putchar('f');
}

void	ft_init_ijk(void)
{
	t_all *all;

	all = ft_singleton();
	all->i = 0;
	all->j = 0;
	all->k = 0;
}

int		ft_main(t_all *all, t_history **history)
{
	char	*line;

	line = NULL;
	if (!ft_push_term(all))
		return (0);
	if (all->prompt == 0)
		ft_putprompt(all);
	else
		all->prompt = 0;
	line = ft_get_line(all, history);
	ft_putchar('\n');
	ft_parse_line(all, line);
	return (1);
}

int		main(int argc, char **argv, char **env)
{
	t_all		*all;
	int			i;
	t_history	*history;

	ft_caps("cl", 1);
	(void)argc;
	(void)argv;
	i = 0;
	history = NULL;
	ft_put_header();
	all = ft_singleton();
	signal(2, sigfunc);
	if (!ft_init_term(all))
		return (0);
	while (env[i])
		i++;
	all->env = ft_tabdup(env, i + 1);
	all->pwd = (char*)ft_memalloc(sizeof(char) * 4096);
	getwd(all->pwd);
	all->pastpwd = ft_strdup(all->pwd);
	while (42)
		if (!ft_main(all, &history))
			return (0);
}
