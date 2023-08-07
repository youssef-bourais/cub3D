/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 17:25:35 by msodor            #+#    #+#             */
/*   Updated: 2023/08/07 17:25:53 by msodor           ###   ########.fr       */
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
	map->player = NULL;
	map->width = 0;
	map->height = 0;
	map->floor = 0;
	map->ceiling = 0;
	map->player_x = 0;
	map->player_y = 0;
}
