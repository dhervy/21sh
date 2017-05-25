/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhervy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:13:56 by dhervy            #+#    #+#             */
/*   Updated: 2017/04/01 20:13:58 by dhervy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sh.h"

int		ft_exec(t_all *all, char **cmd, char **env)
{
	pid_t	proces;
	char	*str;

	str = NULL;
	if (ft_exec_bultin(all, cmd))
		return (1);
	all->fork++;
	proces = fork();
	if (proces == 0)
	{
		ft_exec2(all, cmd, env, str);
		exit(0);
	}
	return (1);
}

int		ft_check_droit(char *str)
{
	struct stat	stats;

	lstat(str, &stats);
	if ((stats.st_mode & S_IXUSR))
	{
		ft_putstr_fd("21sh : Permission Denied.", 2);
		return (0);
	}
	return (1);
}

void	ft_exec2(t_all *all, char **cmd, char **env, char *str)
{
	int		i;
	char	**path;
	int		exec;

	i = 0;
	exec = -1;
	if (ft_searchenv(all->env, "PATH"))
	{
		path = ft_strsplit(ft_searchenv(all->env, "PATH"), ':');
		while (path[i] && exec == -1)
		{
			str = ft_strjoin(path[i], "/");
			str = ft_strjoinfree(str, cmd[0], 0);
			exec = execve(str, cmd, env);
			free(str);
			i++;
		}
	}
	execve(cmd[0], cmd, env);
	ft_putstr("21sh: command not found: ");
	ft_putendl(cmd[0]);
	exit(0);
}

void	ft_exec_arbre(t_arbre **arbre)
{
	t_arbre		*tmp;
	t_all		*all;
	int			i;
	char		**tableau;

	i = 0;
	all = ft_singleton();
	tmp = *arbre;
	if (tmp->token == PIPE)
	{
		ft_exec_pipe(&tmp);
	}
	else if (tmp->token == REDID || tmp->token == DREDID || tmp->token == REDIG\
		|| tmp->token == AGRE || tmp->token == DREDIG)
	{
		ft_exec_redird(&tmp);
	}
	else if (tmp->token == CMD)
	{
		tableau = ft_strsplit_quote(&(tmp->cmd));
		ft_exec(all, tableau, all->env);
		ft_tabfree(tableau);
	}
}

int		ft_get_arbre(t_commande *commande)
{
	t_commande	*tmp;
	t_arbre		*arbre;
	t_all		*all;

	all = ft_singleton();
	all->fork = 0;
	tmp = commande;
	if (!ft_clean_commande(commande))
		return (0);
	ft_create_arbre(&arbre, NULL, &commande);
	all->in = dup(1);
	all->out = dup(0);
	ft_exec_arbre(&arbre);
	while (all->fork-- > 0)
		wait(NULL);
	ft_free_arbre(&arbre);
	dup2(all->in, 1);
	dup2(all->out, 0);
	return (1);
}
