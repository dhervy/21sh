/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplet.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhervy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:13:13 by dhervy            #+#    #+#             */
/*   Updated: 2017/04/01 20:13:15 by dhervy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sh.h"

void	ft_auto_move_left(t_auto **lsauto)
{
	t_auto	*tmp;

	tmp = *lsauto;
	while (tmp && tmp->select == 0)
		tmp = tmp->next;
	tmp->select = 0;
	if (tmp->prev != NULL)
		tmp->prev->select = 1;
	else
	{
		tmp = *lsauto;
		while (tmp->next)
			tmp = tmp->next;
		tmp->select = 1;
	}
}

void	ft_auto_getkey(t_auto **lsauto, t_all *all)
{
	unsigned long	buf;

	buf = 0;
	while (buf != 10)
	{
		buf = 0;
		read(0, (char*)&buf, 8);
		if (buf == RIGHT || buf == TAB)
		{
			ft_auto_move_right(lsauto);
			ft_print_auto(lsauto, all, 0);
		}
		if (buf == LEFT)
		{
			ft_auto_move_left(lsauto);
			ft_print_auto(lsauto, all, 0);
		}
	}
}

char	*ft_auto_getname(t_auto **lsauto, char *debut)
{
	t_auto	*tmp;
	char	*str;
	int		i;

	i = ft_strlen(debut);
	tmp = *lsauto;
	while (tmp && tmp->select == 0)
		tmp = tmp->next;
	str = ft_strdup(&tmp->value[i]);
	return (str);
}

void	ft_auto_free(t_auto **lsauto, char *string, char *path, char *debut)
{
	t_auto	*tmp;
	t_auto	*tmp2;

	free(string);
	free(path);
	free(debut);
	if (lsauto)
	{
		tmp = *lsauto;
		tmp2 = tmp;
		while (tmp2)
		{
			tmp2 = tmp->next;
			free(tmp->value);
			free(tmp);
			tmp = tmp2;
		}
	}
}

char	*ft_auto_complet(char **str, t_all *all)
{
	char	*path;
	char	*debut;
	char	*string;
	char	*retour;
	t_auto	*lsauto;

	lsauto = NULL;
	string = ft_auto_get_string(*str, all->pos_x);
	path = ft_auto_get_path(string);
	debut = ft_auto_get_debut(string);
	if (!ft_create_auto(&lsauto, path, debut))
	{
		ft_auto_free(&lsauto, string, path, debut);
		return (NULL);
	}
	lsauto->select = 1;
	ft_print_auto(&lsauto, all, 0);
	ft_auto_getkey(&lsauto, all);
	ft_caps("cd", 0);
	retour = ft_auto_getname(&lsauto, debut);
	ft_auto_free(&lsauto, string, path, debut);
	return (retour);
}
