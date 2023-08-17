/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourais <ybourais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 12:02:20 by msodor            #+#    #+#             */
/*   Updated: 2023/08/17 09:57:25 by ybourais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	checks()
{
	get_game_info();
	check_map();
	init_player_a(g_elems.player);
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
	int size_x = x + SQUAR_SIZE - 1;
	int size_y = y + SQUAR_SIZE - 1;
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

void draw_grid()
{
    int i = 0;
    while (i < g_elems.height * SQUAR_SIZE)
    {
        int j = 0;
        while (j < g_elems.width * SQUAR_SIZE)
        {
            // if (j % SQUAR_SIZE == 0 || i % SQUAR_SIZE == 0)
            // {
                mlx_put_pixel(image, j, i, BLACK);
            // }
            j++;
        }
        i++;
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
	draw_grid();
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
		int xx = round(norm.x);
		int yy = round(norm.y);
		if(g_elems.map[yy/SQUAR_SIZE][xx/SQUAR_SIZE] != '1')
			mlx_put_pixel(image, round(norm.x), round(norm.y), PURPLE);
		if(g_elems.map[yy/SQUAR_SIZE][xx/SQUAR_SIZE] == '1')
			break;
		norm.x = norm.x + norm.x_step;
		norm.y = norm.y + norm.y_step;
		i++;
	}
}

void	draw_lines(int x, int y)
{
	float new_x = cos(g_elems.player_angle)*100;
	float new_y = sin(g_elems.player_angle)*100;

	// DDA(x, y, x + new_x - sin(-60)*g_elems.width*SQUAR_SIZE, y + new_y + cos(-60)*g_elems.width*SQUAR_SIZE);

	// DDA(x, y, x + new_x + sin(60)*g_elems.width*SQUAR_SIZE, y + new_y + cos(60)*g_elems.width*SQUAR_SIZE);

	// DDA(x, y, x + new_x, y + new_y);
	DDA(x, y, x + new_x, y + new_y);
}

void draw_player(uint32_t color, int x, int y)
{
	g_elems.pos_x_p = x + g_elems.pos_x_p;
	g_elems.pos_y_p = y + g_elems.pos_y_p;
	x = g_elems.pos_x_p;
	y = g_elems.pos_y_p;

	int radius = PLAYER_SIZE / 2;
	int pixel_x = x - radius;

	draw_lines(x, y);

	while (pixel_x <= x + radius)
    {
		int pixel_y = y - radius;
        while (pixel_y <= y + radius)
        {
            if (pow(pixel_x - x, 2) + pow(pixel_y - y, 2) <= pow(radius, 2))
                mlx_put_pixel(image, pixel_x, pixel_y, BLUE);
			pixel_y++;
        }
		pixel_x++;
    }
}

void rotate_player()
{
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		g_elems.player_angle = g_elems.player_angle - 1*M_PI/(double)180;
		plot_map();
		draw_player(BLUE, 0, 0);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		g_elems.player_angle = g_elems.player_angle + 1*M_PI/(double)180;
		plot_map();
		draw_player(BLUE, 0, 0);
	}
}

void keyhook()
{
	int move;
	if (g_elems.player_angle < 0)
		g_elems.player_angle += 2 * PI;
	if (g_elems.player_angle >= 2 * PI)
    	g_elems.player_angle -= 2 * PI;
	move = 2;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_SPACE))
		move = 5;
	rotate_player();
	if (mlx_is_key_down(mlx, MLX_KEY_UP) && g_elems.map[((g_elems.pos_y_p - (PLAYER_SIZE - move))/SQUAR_SIZE)][((g_elems.pos_x_p)/SQUAR_SIZE)] != '1')
	{
		float new_x = sin(g_elems.player_angle) * move;
		float new_y = cos(g_elems.player_angle) * move;
		plot_map();
		draw_player(BLUE, new_x, new_y);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN) && g_elems.map[((g_elems.pos_y_p + (PLAYER_SIZE - move))/SQUAR_SIZE)][((g_elems.pos_x_p)/SQUAR_SIZE)] != '1')
	{
		float new_x = sin(g_elems.player_angle) * move;
		float new_y = cos(g_elems.player_angle) * move;
		plot_map();
		draw_player(BLUE, 0, move);
		draw_player(BLUE, new_x, -new_y);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT) && g_elems.map[((g_elems.pos_y_p)/SQUAR_SIZE)][((g_elems.pos_x_p - (PLAYER_SIZE - move))/SQUAR_SIZE)] != '1')
	{
		float new_x = sin(g_elems.player_angle) * move;
		float new_y = cos(g_elems.player_angle) * move;
		plot_map();
		draw_player(BLUE, new_x,  new_y);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT) && g_elems.map[((g_elems.pos_y_p)/SQUAR_SIZE)][((g_elems.pos_x_p + (PLAYER_SIZE - move))/SQUAR_SIZE)] != '1')
	{
		float new_x = sin(g_elems.player_angle) * move;
		float new_y = cos(g_elems.player_angle) * move;
		plot_map();
		draw_player(BLUE, new_x,  new_y);
	}
}

int	main(int ac, char **av)
{
	if (ac != 2)
		ft_err("Wrong number of arguments\n");
	init_info(av[1]);
	checks();
	plot_map();
	draw_player(BLUE, 0, 0);
	// DDA(g_elems.pos_x_p, g_elems.pos_y_p, g_elems.pos_x_p, g_elems.pos_y_p - 100);
	mlx_loop_hook(mlx, keyhook, NULL);
	mlx_loop(mlx);
}
