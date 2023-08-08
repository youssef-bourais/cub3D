/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourais <ybourais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 12:02:20 by msodor            #+#    #+#             */
/*   Updated: 2023/08/08 19:05:10 by ybourais         ###   ########.fr       */
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
		ft_err("Missing info : player\n");
	if (map->ceiling != 1 || map->floor != 1)
		ft_err("Missing info : colors\n");
}

void draw_square(uint32_t color, int x, int y)
{
	int size_x = x + SQUAR_SIZE - 2;
	int size_y = y + SQUAR_SIZE - 2;
	int firs_y = y;

	while (x < size_x)
	{
		y = firs_y;
		while (y < size_y)
		{
			mlx_put_pixel(image, y, x, color);
			y++;
		}
		x++;
	}
}

void draw_player(uint32_t color, int x, int y, t_elems *map)
{
	int size_x = x + PLAYER_SIZE;
	int size_y = y + PLAYER_SIZE;
	int firs_y = y;
	
	player = mlx_new_image(mlx, PLAYER_SIZE, PLAYER_SIZE);
	mlx_image_to_window(mlx, player, (map->player_y * SQUAR_SIZE) + 17, (map->player_x * SQUAR_SIZE)+ 17);

	while (x < size_x)
	{
		y = firs_y;
		while (y < size_y)
		{
			mlx_put_pixel(player, y, x, color);
			y++;
		}
		x++;
	}
}

void plot_map(t_elems *map)
{
	int i = 0;

	mlx = mlx_init(SQUAR_SIZE * map->width, SQUAR_SIZE * map->height, "MLX42", 0);

	image = mlx_new_image(mlx, SQUAR_SIZE * map->width, SQUAR_SIZE * map->height);
	mlx_image_to_window(mlx, image, 0, 0);

	i = 0;
	while (i < map->height)
	{
		int j = 0;
		while (map->map[i][j] != '\0')
		{
			if(map->map[i][j] == '1')
				draw_square(RED, SQUAR_SIZE * i, SQUAR_SIZE * j);
			else if (map->map[i][j] != ' ')
				draw_square(WHITE, SQUAR_SIZE * i, SQUAR_SIZE * j);
			j++;
		}
		i++;
	}
}

void keyhook(void* param)
{
	int move;

	move = 2;
	if(mlx_is_key_down(mlx, MLX_KEY_SPACE))
		move = 5;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		player->instances->y -= move;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		player->instances->y += move;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		player->instances->x -= move;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		player->instances->x += move;
}

int	main(int ac, char **av)
{
	t_elems	map;

	if (ac != 2)
		ft_err("Wrong number of arguments\n");
	init_info(&map, av[1]);
	checks(&map);
	plot_map(&map);
	draw_player(BLUE, 0, 0, &map);
	mlx_loop_hook(mlx, keyhook, mlx);
	mlx_loop(mlx);
}
