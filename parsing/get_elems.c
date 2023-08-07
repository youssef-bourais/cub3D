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

int	is_unmber(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return 1;
		i++;
	}
	return 0;
}

int is_rgb(int nbr)
{
	if (nbr < 0 || nbr > 255)
		return 1;
	return 0;
}

int set_f_color(t_elems *map, char **info)
{
	char **rgb;

	rgb = ft_split(info[1], ",");
	if (!rgb[0] || !rgb[1] || !rgb[2])
		return 1;
	if (is_unmber(rgb[0]) || is_unmber(rgb[1]) || is_unmber(rgb[2]))
		return 1;
	map->f_color[0] = ft_atoi(rgb[0]);
	map->f_color[1] = ft_atoi(rgb[1]);
	map->f_color[2] = ft_atoi(rgb[2]);
	map->floor += 1;
	if (is_rgb(map->f_color[0]) || is_rgb(map->f_color[1]) || is_rgb(map->f_color[2]))
		return 1;
	free_array(rgb);
	return 0;
}
int set_c_color(t_elems *map, char **info)
{
	char **rgb;

	rgb = ft_split(info[1], ",");
	if (!rgb[0] || !rgb[1] || !rgb[2])
		return 1;
	if (is_unmber(rgb[0]) || is_unmber(rgb[1]) || is_unmber(rgb[2]))
	map->c_color[0] = ft_atoi(rgb[0]);
	map->c_color[1] = ft_atoi(rgb[1]);
	map->c_color[2] = ft_atoi(rgb[2]);
	map->ceiling += 1;
	if (is_rgb(map->c_color[0]) || is_rgb(map->c_color[1]) || is_rgb(map->c_color[2]))
		return 1;
	free_array(rgb);
	return 0;
}

int	set_info(t_elems *map, char **info)
{
	if(!info[0])
		return 0;
	else if (!strcmp(info[0], "EA") && !map->ea && info[1])
		return map->ea = ft_strdup(info[1]), 0;
	else if (!strcmp(info[0], "NO") && !map->no && info[1])
		return map->no = ft_strdup(info[1]), 0;
	else if (!strcmp(info[0], "SO") && !map->so && info[1])
		return map->so = ft_strdup(info[1]), 0;
	else if (!strcmp(info[0], "WE") && !map->we && info[1])
		return map->we = ft_strdup(info[1]), 0;
	else if (!strcmp(info[0], "F"))
	{
		if (set_f_color(map, info) == 1)
			return 1;
	}
	else if (!strcmp(info[0], "C"))
	{
		if (set_c_color(map, info) == 1)
			return 1;
	}
	else
		return 1;
	return 0;
}

void	width_height(t_elems *elems)
{
	int i;

	i = 0;
	while (elems->map[elems->height])
		elems->height++;
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
		{

			break;
		}
		free_array(info);
		line = get_next_line(map->fd);
	}
	while (line)
	{
		one_line = f_strjoin(one_line, line);
		line = get_next_line(map->fd);
	}
	map->map = ft_split(one_line, "\n");
	width_height(map);
}

int is_map_comp(char c)
{
	if (c == '1' || c == '0' || c == ' ')
		return 1;
	return 0;
}

int is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return 1;
	return 0;
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
			if (!is_map_comp(elem->map[i][j]) && !is_player(elem->map[i][j]))
				return 1;
			if (is_player(elem->map[i][j]))
			{
				if (elem->player)
					return 1;
				elem->player_x = i;
				elem->player_y = j;
				elem->player = ft_strdup(&elem->map[i][j]);
			}
			j++;
		}
		i++;
	}
	return 0;
}

int check_l_r_wall(t_elems *elems)
{
	int i;

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
	return 0;
}

int check_t_b_wall(t_elems *elems)
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
	while (elems->map[elems->height - 1][i])
	{
		if (elems->map[elems->height - 1][i] != '1' \
		&& elems->map[elems->height - 1][i] != ' ')
			return 1;
		i++;
	}
	return 0;
}
int	check_wals(t_elems *elems)
{
	if (check_l_r_wall(elems) || check_t_b_wall(elems))
		return 1;
	return 0;
}
int wall_player(char c)
{
	if (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return 1;
	return 0;
}
int	check_map_closed(t_elems *elem)
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
				if (!wall_player(elem->map[i][j + 1]) || !wall_player(elem->map[i][j - 1]) \
				|| !wall_player(elem->map[i + 1][j]) || !wall_player(elem->map[i - 1][j]))
					return 1;
			}
			j++;
		}
		i++;
	}
	return 0;
}
