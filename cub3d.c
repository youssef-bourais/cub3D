/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourais <ybourais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 12:02:20 by msodor            #+#    #+#             */
/*   Updated: 2023/08/10 10:52:02 by ybourais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	checks()
{
	get_game_info();
	check_map();
	check_map_closed();
	check_wals();
	if (!g_elems.ea || !g_elems.no || !g_elems.so || !g_elems.we)
		ft_err("Missing info : texturs\n");
	if (!g_elems.player)
		ft_err("Missing info : player\n");
	if (g_elems.ceiling != 1 || g_elems.floor != 1)
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
			mlx_put_pixel(image, x, y, color);
			y++;
		}
		x++;
	}
}

void plot_map()
{
	int i = 0;
	int static b;

	if(b == 0)
	{
		mlx = mlx_init(SQUAR_SIZE * g_elems.width, SQUAR_SIZE * g_elems.height, "GAME", 0);

		image = mlx_new_image(mlx, SQUAR_SIZE * g_elems.width, SQUAR_SIZE * g_elems.height);
		mlx_image_to_window(mlx, image, 0, 0);
		b++;
	}

	i = 0;
	while (i < g_elems.height)
	{
		int j = 0;
		while (g_elems.map[i][j] != '\0')
		{
			if(g_elems.map[i][j] == '1')
				draw_square(RED, SQUAR_SIZE * j, SQUAR_SIZE * i);
			else if (g_elems.map[i][j] != ' ')
				draw_square(WHITE, SQUAR_SIZE * j, SQUAR_SIZE * i);
			j++;
		}
		i++;
	}
}

void draw_player(uint32_t color, int x, int y)
{
	int t = y;
	x = (g_elems.player_x * SQUAR_SIZE) + 17 + x;
	y = (g_elems.player_y * SQUAR_SIZE) + 17 + y;

	int size_x = x + PLAYER_SIZE;
	int size_y = y + PLAYER_SIZE;

	while (x < size_x)
	{
		y = (g_elems.player_y * SQUAR_SIZE) + 17 + t;
		while (y < size_y)
		{
			mlx_put_pixel(image, x, y, color);
			y++;
		}
		x++;
	}
}

void keyhook()
{
	int move;

	move = 2;
	if(mlx_is_key_down(mlx, MLX_KEY_SPACE))
		move = 5;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
	{
		plot_map();
		draw_player(BLUE, 0, -move);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
	{
		plot_map();
		draw_player(BLUE, 0, move);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		plot_map();
		draw_player(BLUE, -move, 0);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		plot_map();
		draw_player(BLUE, move, 0);
	}
}

void DDA(int x0, int y0, int x1, int y1)
{
	t_norm norm;
    norm.dx = x1 - x0;
    norm.dy = y1 - y0;
	int steps;

	if (abs(norm.dx) >= abs(norm.dy))
		steps = abs(norm.dx);
	else
		steps = abs(norm.dy);
    norm.x = x0;
    norm.y = y0;
	norm.x_step = (float)norm.dx / steps;
	norm.y_step = (float)norm.dy / steps;

	int i = 0;
	while (i <= steps)
	{
		mlx_put_pixel(image, round(norm.x), round(norm.y), YELLOW);
		norm.x = norm.x + norm.x_step;
		norm.y = norm.y + norm.y_step;
		i++;
	}
}

// void DDA(int x0, int y0, int x1, int y1)
// {
// 	t_norm norm;
//     norm.dx = x1 - x0;
//     norm.dy = y1 - y0;

// 	if (abs(norm.dx) >= abs(norm.dy))
// 		norm.steps = abs(norm.dx);
// 	else
// 		norm.steps = abs(norm.dy);

// 	norm.slope = (float)norm.dy/norm.dx;
//     norm.x = x0;
//     norm.y = y0;
// 	int i;
// 	if (norm.slope < 1)
// 	{
// 		i = 0;
// 		while (i <= norm.steps)
// 		{
// 			mlx_put_pixel(image, norm.x, norm.y, YELLOW);
// 			norm.x = round(norm.x + 1);
// 			norm.y = round(norm.y + norm.slope);
// 			i++;
// 		}
// 	}
// 	else if (norm.slope == 1)
// 	{
// 		i = 0;
// 		while (i <= norm.steps)
// 		{
// 			mlx_put_pixel(image, norm.x, norm.y, YELLOW);
// 			norm.x = round(norm.x + 1);
// 			norm.y = round(norm.y + 1);
// 			i++;
// 		}
// 	}
// 	else if (norm.slope > 1)
// 	{
// 		i = 0;
// 		while (i <= norm.steps)
// 		{
// 			mlx_put_pixel(image, norm.x, norm.y, YELLOW);
// 			norm.x = round(norm.x + (1/norm.slope));
// 			norm.y = round(norm.y + 1);
// 			i++;
// 		}
// 	}
// }

int	main(int ac, char **av)
{
	if (ac != 2)
		ft_err("Wrong number of arguments\n");
	init_info(av[1]);
	checks();
	plot_map();
	draw_player(BLUE, 0, 0);
	// DDA(g_elems.player_x * SQUAR_SIZE + 17 + PLAYER_SIZE/2, g_elems.player_y * SQUAR_SIZE + 17, g_elems.player_x * SQUAR_SIZE + 17 + PLAYER_SIZE/2, 100);
	mlx_loop_hook(mlx, keyhook, mlx);
	mlx_loop(mlx);
}
