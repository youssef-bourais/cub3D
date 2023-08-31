/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:21:19 by msodor            #+#    #+#             */
/*   Updated: 2023/08/31 15:40:40 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_info(char **info)
{
	if (!info[0])
		return ;
	else if (!strcmp(info[0], "EA") && !g_elems.ea && info[1])
		g_elems.ea = ft_strdup(info[1]);
	else if (!strcmp(info[0], "NO") && !g_elems.no && info[1])
		g_elems.no = ft_strdup(info[1]);
	else if (!strcmp(info[0], "SO") && !g_elems.so && info[1])
		g_elems.so = ft_strdup(info[1]);
	else if (!strcmp(info[0], "WE") && !g_elems.we && info[1])
		g_elems.we = ft_strdup(info[1]);
	else if (!strcmp(info[0], "F"))
		set_f_color(info);
	else if (!strcmp(info[0], "C"))
		set_c_color(info);
	else
	{
		free_array(info);
		ft_err("Invalid element\n");
	}
}

void	width_height(void)
{
	int	i;

	i = 0;
	while (g_elems.map[g_elems.height])
		g_elems.height++;
	while (g_elems.map[i])
	{
		if (ft_strlen(g_elems.map[i]) > g_elems.width)
			g_elems.width = ft_strlen(g_elems.map[i]);
		i++;
	}
}

int	is_all_wall(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '1')
			return (1);
		i++;
	}
	return (0);
}

void	separated_map(char *one_line_map)
{
	int	i;

	i = 0;
	while (one_line_map[i])
	{
		if (one_line_map[i] == '\n' && one_line_map[i + 1]
			&& one_line_map[i + 1] == '\n')
			ft_err("Invalid map\n");
		i++;
	}
}

void	get_game_info(void)
{
	char	*line;
	char	**info;
	char	*one_line;

	one_line = NULL;
	line = get_next_line(g_elems.fd);
	while (line)
	{
		info = ft_split(line, " \t\n");
		if (info[0] && is_all_wall(info[0]) == 0)
			break ;
		set_info(info);
		free_array(info);
		free(line);
		line = get_next_line(g_elems.fd);
	}
	while (line)
	{
		one_line = f_strjoin(one_line, line);
		free(line);
		line = get_next_line(g_elems.fd);
	}
	separated_map(one_line);
	g_elems.map = ft_split(one_line, "\n");
	if (!g_elems.map)
		ft_err("Invalid map\n");
}
