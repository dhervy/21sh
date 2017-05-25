/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhervy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 13:03:06 by dhervy            #+#    #+#             */
/*   Updated: 2017/04/02 13:03:20 by dhervy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sh.h"

int		ft_exec_pipe(t_arbre **arbre)
{
	int		child;
	int		pdes[2];
	t_arbre	*tmp;
	t_all	*all;

	all = ft_singleton();
	tmp = *arbre;
	pipe(pdes);
	all->fork++;
	child = fork();
	if (child == 0)
	{
		dup2(pdes[1], STDOUT_FILENO);
		close(pdes[0]);
		ft_exec_arbre(&tmp->left);
		exit(0);
	}
	else if (child > 0)
	{
		dup2(pdes[0], STDIN_FILENO);
		close(pdes[1]);
		ft_exec_arbre(&tmp->right);
	}
	return (0);
}

int		ft_get_fd(char *str)
{
	char	c;

	c = str[0];
	if (!ft_isdigit(c))
		return (1);
	else
		return (ft_atoi(str));
}

int		ft_get_fd2(char *str)
{
	if (str[0] == '-')
		return (-1);
	else
		return (ft_atoi(str));
}

void	ft_init_tabfd(t_all *all)
{
	ft_bzero(all->tabfd, 256);
	all->tabfd[0] = 0;
	all->tabfd[1] = 1;
	all->tabfd[2] = 2;
}
