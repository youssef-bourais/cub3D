/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 12:02:20 by msodor            #+#    #+#             */
/*   Updated: 2023/08/08 00:37:22 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	checks(t_elems *map)
{
	get_game_info(map);
	check_map(map);
	check_map_closed(map);
	check_wals(map);
	if (!map->ea || !map->no || !map->so || !map->we)
		ft_err("Missing info : texturs\n");
	if (!map->player)
	{
		// printf("%s\n", map->player);
		ft_err("Missing info : player\n");
	}
	if (map->ceiling != 1 || map->floor != 1)
		ft_err("Missing info : colors\n");
}

int	main(int ac, char **av)
{
	t_elems	map;

	if (ac != 2)
		ft_err("Wrong number of arguments\n");
	init_info(&map, av[1]);
	checks(&map);
}
