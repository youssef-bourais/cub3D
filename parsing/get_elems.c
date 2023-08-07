/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_game_info.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:31:09 by msodor            #+#    #+#             */
/*   Updated: 2023/08/03 10:27:22 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_info(t_elems *map, char *file)
{
	map->file = file;
	map->fd = open(map->file, O_RDONLY);
	map->ea = NULL;
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
	map->map = NULL;
	map->width = 0;
	map->height = 0;
}
void	free_array(char **array)
{
	int i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
int	set_info(t_elems *map, char **info)
{
	char **rgb;

	if(!info[0])
		return 0;
	if (!strcmp(info[0], "EA") && !map->ea && info[1])
		return map->ea = ft_strdup(info[1]), 0;
	else if (!strcmp(info[0], "NO") && !map->no && info[1])
		return map->no = ft_strdup(info[1]), 0;
	else if (!strcmp(info[0], "SO") && !map->so && info[1])
		return map->so = ft_strdup(info[1]), 0;
	else if (!strcmp(info[0], "WE") && !map->we && info[1])
		return map->we = ft_strdup(info[1]), 0;
	else if (!strcmp(info[0], "F"))
	{
		rgb = ft_split(info[1], ",");
		if (!rgb[0] || !rgb[1] || !rgb[2])
			return 1;
		map->f_color[0] = ft_atoi(rgb[0]);
		map->f_color[1] = ft_atoi(rgb[1]);
		map->f_color[2] = ft_atoi(rgb[2]);
		map->floor = 1;
		free_array(rgb);
		return 0;
	}
	else if (!strcmp(info[0], "C"))
	{
		rgb = ft_split(info[1], ",");
		if (!rgb[0] || !rgb[1] || !rgb[2])
			return 1;
		map->c_color[0] = ft_atoi(rgb[0]);
		map->c_color[1] = ft_atoi(rgb[1]);
		map->c_color[2] = ft_atoi(rgb[2]);
		map->ceiling = 1;
		free_array(rgb);
		return 0;
	}
	else
		return 1;
}

void	hight(t_elems *elems)
{
	while (elems->map[elems->height])
		elems->height++;
}
void	width(t_elems *elems)
{
	int i;

	i = 0;
	while (elems->map[i])
	{
		if (ft_strlen(elems->map[i]) > elems->width)
			elems->width = ft_strlen(elems->map[i]);
		i++;
	}
}
void	get_game_info(t_elems *map)
{
	char *line;
	char **info;
	char *one_line = NULL;

	line = get_next_line(map->fd);
	while(line)
	{
		info = ft_split(line, " \t\n");
		if (set_info(map, info) == 1)
			break;
		free_array(info);
		line = get_next_line(map->fd);
	}
	while (line)
	{
		one_line = f_strjoin(one_line, line);
		line = get_next_line(map->fd);
	}
	map->map = ft_split(one_line, "\n");
	hight(map);
	width(map);
}
int check_map(t_elems *elem)
{
	int i;
	int j;

	i = 0;
	while (elem->map[i])
	{
		j = 0;
		while (elem->map[i][j])
		{
			if (elem->map[i][j] != '1' && elem->map[i][j] != '0' \
			&& elem->map[i][j] != ' ' && elem->map[i][j] != 'N' \
			&& elem->map[i][j] != 'S' && elem->map[i][j] != 'W' \
			&& elem->map[i][j] != 'E')
				return 1;
			j++;
		}
		i++;
	}
	return 0;
}

int check_wals(t_elems *elems)
{
	int i;
	int j;

	j = 0;
	while (elems->map[0][j])
	{
		if (elems->map[0][j] != '1' && elems->map[0][j] != ' ')
			return 1;
		j++;
	}
	i = 0;
	while (elems->map[i])
	{
		if (elems->map[i][0] != '1' && elems->map[i][0] != ' ')
			return 1;
		i++;
	}
	i = 0;
	while (elems->map[i])
	{
		if (elems->map[i][ft_strlen(elems->map[i]) - 1] != '1' \
		&& elems->map[i][ft_strlen(elems->map[i]) - 1] != ' ')
			return 1;
		i++;
	}
	i = 0;
	while (elems->map[elems->height - 1][i])
	{
		if (elems->map[elems->height - 1][i] != '1' \
		&& elems->map[elems->height - 1][i] != ' ')
			return 1;
		i++;
	}
	return 0;
}
int check_map_closed(t_elems *elem)
{
	int i;
	int j;

	i = 0;
	while (elem->map[i])
	{
		j = 0;
		while (elem->map[i][j])
		{
			if (elem->map[i][j] == '0')
			{
				if (elem->map[i][j + 1] == ' ' || elem->map[i][j - 1] == ' ' \
				|| elem->map[i + 1][j] == ' ' || elem->map[i - 1][j] == ' ')
					return 1;
			}
			j++;
		}
		i++;
	}
	return 0;
}