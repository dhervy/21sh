/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhervy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 15:18:04 by dhervy            #+#    #+#             */
/*   Updated: 2017/03/14 04:00:48 by dhervy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sh.h"

char	**ft_get_multi_commande(t_all *all, char *line, char **multi_line)
{
	ft_init_ijk();
	if (!ft_strcmp(line, ";;"))
		return (NULL);
	while (line[all->i])
	{
		if (line[all->i] == ';' && line[all->i + 1] != '\0' && all->i > 0)
			all->j++;
		if (line[all->i] == '\'' || line[all->i] == '\"')
			all->i = ft_check_quote(line, all->i);
		all->i++;
	}
	multi_line = (char **)ft_memalloc(sizeof(char*) * all->j + 1);
	all->j = 0;
	all->i = 0;
	while (line[all->i])
	{
		if (!ft_get_multi_commande2(all, line, multi_line))
			return (NULL);
	}
	if (line[all->i] == '\0' && line[all->i - 1] != ';')
		multi_line[all->j++] = ft_strdup(&line[all->k]);
	multi_line[all->j] = NULL;
	return (multi_line);
}

char	**ft_clean_multi2(t_all *all, char **str)
{
	str = (char **)ft_memalloc(sizeof(char *) * all->k + 1);
	all->i = 0;
	all->k = 0;
	return (str);
}

char	**ft_clean_multi(t_all *all, char **multi, char **str)
{
	str = NULL;
	ft_init_ijk();
	while (multi[all->i])
	{
		while (multi[all->i][all->j] == ' ')
			all->j++;
		if (multi[all->i][all->j] != '\0')
			all->k++;
		all->j = 0;
		all->i++;
	}
	str = ft_clean_multi2(all, str);
	while (multi[all->i])
	{
		while (multi[all->i][all->j] == ' ')
			all->j++;
		if (multi[all->i][all->j] != '\0')
			str[all->k++] = ft_strdup(multi[all->i]);
		all->j = 0;
		all->i++;
	}
	str[all->k] = NULL;
	ft_tabfree(multi);
	return (str);
}

char	*ft_clean_space(char *line)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = ft_strlen(line) - 1;
	str = NULL;
	while (line[i])
	{
		if (ft_isspace(line[i]))
			line[i] = ' ';
		i++;
	}
	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '\0')
		return (ft_delete_space(line));
	while (line[j] == ' ')
		j--;
	str = line;
	line = ft_strndup(&line[i], (j - i) + 1);
	free(str);
	line = ft_delete_space(line);
	return (line);
}

int		ft_parse_line(t_all *all, char *line)
{
	char		**multi_line;
	int			i;

	multi_line = NULL;
	multi_line = ft_get_multi_commande(all, line, multi_line);
	if (*line == '\0')
		return (ft_free_line_tab(line, multi_line));
	if (multi_line == NULL)
	{
		free(line);
		ft_putstr("21sh: parse error near `;;'\n");
		return (-1);
	}
	i = -1;
	while (multi_line[++i])
		multi_line[i] = ft_clean_space(multi_line[i]);
	multi_line = ft_clean_multi(all, multi_line, NULL);
	if (ft_get_parser(multi_line) == -1)
	{
		if (line)
			free(line);
		return (-1);
	}
	ft_free_line_tab(line, multi_line);
	return (0);
}
