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
	// map->ceiling = 0;
	// map->floor = 0;
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
	if (!strcmp(info[0], "EA") && !map->ea)
		return map->ea = ft_strdup(info[1]), 0;
	else if (!strcmp(info[0], "NO") && !map->no)
		return map->no = ft_strdup(info[1]), 0;
	else if (!strcmp(info[0], "SO") && !map->so)
		return map->so = ft_strdup(info[1]), 0;
	else if (!strcmp(info[0], "WE") && !map->we)
		return map->we = ft_strdup(info[1]), 0;
	else if (!strcmp(info[0], "F"))
	{
		rgb = ft_split(info[1], ",");
		map->floor[0] = ft_atoi(rgb[0]);
		map->floor[1] = ft_atoi(rgb[1]);
		map->floor[2] = ft_atoi(rgb[2]);
		free_array(rgb);
		return 0;
	}
	else if (!strcmp(info[0], "C"))
	{
		rgb = ft_split(info[1], ",");
		map->ceiling[0] = ft_atoi(rgb[0]);
		map->ceiling[1] = ft_atoi(rgb[1]);
		map->ceiling[2] = ft_atoi(rgb[2]);
		free_array(rgb);
		return 0;
	}
	else
		return 1;
}

void	get_game_info(t_elems *map)
{
	char *line;
	char **info;
	char *one_line;

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
		one_line = ft_strjoin(one_line, line);
		line = get_next_line(map->fd);
	}
	printf("%s\n", one_line);
	

}