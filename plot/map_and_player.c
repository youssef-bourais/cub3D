/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_and_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourais <ybourais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 11:06:56 by ybourais          #+#    #+#             */
/*   Updated: 2023/08/26 00:51:50 by ybourais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
			mlx_put_pixel(image, j, i, BLACK);
            j++;
        }
        i++;
    }
}

void welcome()
{
	int y = 120;
	while (y < HEIGHT - 120)
	{
		int x = 0; // 50 = SQUARE_SIZE with map_height
		// int k = HEIGHT - 50;
		while(x < WIDTH)
		{
			// WELCOME
			mlx_put_pixel(image, x, y, BLACK);
			x++;
			// k--;
		}
		y++;
	}
	
}

void _2_to_3d()
{
	float coefficient;
	// float y_start = 120 + g_elems;
	coefficient *= 1;
	float y_end;
	int x = 0;
	float up_y = 0;;
	float down_y = 0;

	up_y = 120;
	down_y = 510 + 120;
	plot_sky_and_land();
	while (x < WIDTH)
	{
		// DDA(x, 120, x, 510 + 120, YELLOW);	
		DDA(x, up_y + g_elems.ray_distante[x], x, down_y - g_elems.ray_distante[x], ORANGE);	
		// DDA(510, x, 510, x, YELLOW);	
		// int x = 0; // 50 = SQUARE_SIZE with map_height
		// int k = HEIGHT - 50;
		// while(x < WIDTH)
		// {
		// print_line_distance();
		// DDA();
		// mlx_put_pixel(image, x, y, YELLOW);
		// x++;
		// k--;
		x++;
	}
}

void draw_player(uint32_t color, float x, float y)
{
	g_elems.pos_x_p = x + g_elems.pos_x_p;
	g_elems.pos_y_p = y + g_elems.pos_y_p;
	x = g_elems.pos_x_p;
	y = g_elems.pos_y_p;

	int radius = PLAYER_SIZE / 2;
	int pixel_x = x - radius;
	cast_rays();
	// draw_line(x, y);
	while (pixel_x < x + radius)
    {
		int pixel_y = y - radius;
        while (pixel_y <= y + radius)
        {
            if (pow(pixel_x - x, 2) + pow(pixel_y - y, 2) <= pow(radius, 2))
                mlx_put_pixel(image, pixel_x, pixel_y, color);
			pixel_y++;
        }
		pixel_x++;
    }
}

void DDA(int x0, int y0, int x1, int y1, uint32_t color)
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
		mlx_put_pixel(image, round(norm.x), round(norm.y), color);
		norm.x = norm.x + norm.x_step;
		norm.y = norm.y + norm.y_step;
		i++;
	}
}

void plot_sky_and_land()
{
	int i = 0;
	while (i < HEIGHT)
	{
		int j = 0;
		while (j < WIDTH)
		{
			if (i <= HEIGHT/2)
				mlx_put_pixel(image, j, i, BLUE);
			else
				mlx_put_pixel(image, j, i, GREEN);
			j++;
		}
		i++;
	}
	
}

void init_image()
{
	mlx = mlx_init(WIDTH, HEIGHT, "GAME", 0);
	image = mlx_new_image(mlx, WIDTH, HEIGHT);
	mlx_image_to_window(mlx, image, 0, 0);
}
void plot_map()
{
	int i;
	
	draw_grid();
	i = 0;
	while (g_elems.map[i])
	{
		int j = 0;
		while (g_elems.map[i][j])
		{
			if(g_elems.map[i][j] == '1')
				draw_square(RED, (SQUAR_SIZE) * j, (SQUAR_SIZE) * i);
			else if (g_elems.map[i][j] != ' ')
				draw_square(GRAY, (SQUAR_SIZE) * j, (SQUAR_SIZE) * i);
			j++;
		}
		i++;
	}
}
