/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhervy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:13:25 by dhervy            #+#    #+#             */
/*   Updated: 2017/04/01 20:13:27 by dhervy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sh.h"

void	ft_cderror(char *str)
{
	ft_putstr_fd("cd: no such file or directory: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(" OR Permission denied", 2);
}

void	ft_cdhome(t_all *all, DIR *dir)
{
	char	*pwd;
	char	*oldpwd;
	char	*tmp;

	if (ft_searchenv(all->env, "HOME"))
	{
		tmp = ft_strdup(ft_searchenv(all->env, "HOME"));
		pwd = ft_strdup("PWD");
		oldpwd = ft_strdup("OLDPWD");
		dir = opendir(tmp);
		if (dir != NULL)
		{
			free(all->pastpwd);
			all->pastpwd = ft_strdup(all->pwd);
			chdir(tmp);
			all->env = ft_addenv(all->env, pwd, getwd(all->pwd));
			all->env = ft_addenv(all->env, oldpwd, all->pastpwd);
			closedir(dir);
		}
		else
			ft_cderror(all->pastpwd);
		free(tmp);
		free(pwd);
		free(oldpwd);
	}
}

void	ft_cdreturn(t_all *all, DIR *dir)
{
	char	*pwd;
	char	*oldpwd;

	pwd = NULL;
	oldpwd = NULL;
	pwd = ft_strdup("PWD");
	oldpwd = ft_strdup("OLDPWD");
	if ((dir = opendir(all->pastpwd)))
	{
		chdir(all->pastpwd);
		ft_strdel(&all->pastpwd);
		all->pastpwd = ft_strdup(all->pwd);
		all->env = ft_addenv(all->env, pwd, getwd(all->pwd));
		all->env = ft_addenv(all->env, oldpwd, all->pastpwd);
		closedir(dir);
	}
	else
		ft_cderror(all->pastpwd);
	ft_strdel(&pwd);
	ft_strdel(&oldpwd);
}

void	ft_cdrep(t_all *all, char **str, DIR *dir)
{
	char	*pwd;
	char	*oldpwd;

	pwd = NULL;
	oldpwd = NULL;
	pwd = ft_strdup("PWD");
	oldpwd = ft_strdup("OLDPWD");
	dir = opendir(str[1]);
	if (dir != NULL)
	{
		ft_strdel(&all->pastpwd);
		all->pastpwd = ft_strdup(all->pwd);
		chdir(str[1]);
		all->env = ft_addenv(all->env, pwd, getwd(all->pwd));
		all->env = ft_addenv(all->env, oldpwd, all->pastpwd);
		closedir(dir);
	}
	else
		ft_cderror(str[1]);
	ft_strdel(&pwd);
	ft_strdel(&oldpwd);
}

void	ft_cdshell(t_all *all, char **str)
{
	DIR		*dir;

	dir = NULL;
	if (!ft_strcmp(str[0], "cd"))
	{
		if (ft_tablen(str) <= 2)
		{
			if (ft_tablen(str) == 1)
				ft_cdhome(all, dir);
			else if (!ft_strcmp(str[1], "-"))
				ft_cdreturn(all, dir);
			else
				ft_cdrep(all, str, dir);
		}
		else
			ft_putstr_fd("cd: too many arguments\n", 2);
	}
}
