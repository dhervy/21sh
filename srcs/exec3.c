/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhervy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 13:05:00 by dhervy            #+#    #+#             */
/*   Updated: 2017/04/02 13:05:14 by dhervy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sh.h"

void	ft_redird(t_all *all, t_arbre *tmp2)
{
	int		fd;
	int		fd2;

	if (tmp2->top->token == REDID)
	{
		if (ft_isdigit(tmp2->top->cmd[0]))
			fd2 = ft_ctoi(tmp2->top->cmd[0]);
		else
			fd2 = 1;
		fd = open(tmp2->top->right->cmd, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd, all->tabfd[fd2]);
	}
	if (tmp2->top->token == DREDID)
	{
		if (ft_isdigit(tmp2->top->cmd[0]))
			fd2 = ft_ctoi(tmp2->top->cmd[0]);
		else
			fd2 = 1;
		fd = open(tmp2->top->right->cmd, O_WRONLY | O_CREAT | O_APPEND, 0644);
		dup2(fd, all->tabfd[fd2]);
	}
}

void	ft_agre(t_all *all, t_arbre *tmp2)
{
	int		fd;
	int		fd2;

	if (tmp2->top->token == AGRE)
	{
		if (ft_isdigit(tmp2->top->cmd[0]))
			fd2 = ft_ctoi(tmp2->top->cmd[0]);
		else
			fd2 = 1;
		if (tmp2->top->right->cmd[0] == '-')
			fd = -1;
		else
			fd = ft_atoi(tmp2->top->right->cmd);
		if (fd >= 0)
			dup2(all->tabfd[fd], all->tabfd[fd2]);
		else
			close(all->tabfd[fd2]);
	}
}

void	ft_redirg(t_all *all, t_arbre *tmp2)
{
	int		fd;
	int		fd2;

	if (tmp2->top->token == REDIG)
	{
		if (ft_isdigit(tmp2->top->cmd[0]))
			fd2 = ft_ctoi(tmp2->top->cmd[0]);
		else
			fd2 = 0;
		fd = open(tmp2->top->right->cmd, O_RDONLY, 0644);
		dup2(fd, all->tabfd[fd2]);
	}
}

void	ft_dredirg(t_arbre *tmp2)
{
	int		pdes[2];
	int		child;

	if (tmp2->top->token == DREDIG)
	{
		pipe(pdes);
		child = fork();
		if (child == 0)
		{
			dup2(pdes[1], STDOUT_FILENO);
			close(pdes[0]);
			ft_putendl(tmp2->top->right->cmd);
			exit(0);
		}
		else if (child > 0)
		{
			wait(NULL);
			dup2(pdes[0], STDIN_FILENO);
			close(pdes[1]);
		}
	}
}

int		ft_exec_redird(t_arbre **arbre)
{
	t_arbre	*tmp;
	t_arbre	*tmp2;
	t_all	*all;
	char	**tableau;

	tmp = *arbre;
	tmp2 = tmp;
	all = ft_singleton();
	ft_init_tabfd(all);
	while (tmp2->token != CMD)
		tmp2 = tmp2->left;
	all->cmd = ft_strdup(tmp2->cmd);
	while (tmp2 != tmp)
	{
		ft_redird(all, tmp2);
		ft_agre(all, tmp2);
		ft_redirg(all, tmp2);
		ft_dredirg(tmp2);
		tmp2 = tmp2->top;
	}
	tableau = ft_strsplit_quote(&(all->cmd));
	ft_exec(all, tableau, all->env);
	ft_tabfree(tableau);
	free(all->cmd);
	return (0);
}
