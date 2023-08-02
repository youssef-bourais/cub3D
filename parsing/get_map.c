/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:31:09 by msodor            #+#    #+#             */
/*   Updated: 2023/08/02 15:27:50 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_info(t_map map, char *file)
{
	map.file = file;
	map.fd = open(map.file, O_RDONLY);
	map.ea = NULL;
	map.no = NULL;
	map.so = NULL;
	map.we = NULL;
	map.ceiling = NULL;
	map.floor = NULL;
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
void	set_info(t_map map, char **info)
{
		if (strcmp(info[0], "EA"))
			map.ea = info[1];
		else if (strcmp(info[0], "NO"))
			map.no = info[1];
		else if (strcmp(info[0], "SO"))
			map.so = info[1];
		else if (strcmp(info[0], "WE"))
			map.we = info[1];
		else if (strcmp(info[0], "F"))
			map.floor = info[1];
		else if (strcmp(info[0], "C"))
			map.ceiling = info[1];
		else
			printf("Error\n");
}

void	get_map(t_map map)
{
	char *line;
	char **info;
	while((line = get_next_line(map.fd)))
	{
		info = ft_split(line, ' ');
		set_info(map, info);
		free(line);
		free_array(info);
	}
}