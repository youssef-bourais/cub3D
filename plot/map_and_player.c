/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_and_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 11:06:56 by ybourais          #+#    #+#             */
/*   Updated: 2023/08/31 15:45:47 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void draw_square(uint32_t color, int x, int y)
{
	int size_x = x + SQUAR_SIZE;
	int size_y = y + SQUAR_SIZE;
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

void plot_sky_and_land()
{
	int i = 0;
	while (i < HEIGHT)
	{
		int j = 0;
		while (j < WIDTH)
		{
			if (i <= HEIGHT/2)
				mlx_put_pixel(image, j, i, DARK_BLUE);
			else
				mlx_put_pixel(image, j, i, DARK_GREEN);
			j++;
		}
		i++;
	}
}

void get_y_coordinate(float *y0, float *y1, float ray_distance, double ray_angle)
{
	int static b;
	float wall_height;

	ray_distance = ray_distance*cos(g_elems.player_a - ray_angle);
	wall_height = (SQUAR_SIZE*HEIGHT)/ray_distance;

	*y0 = HEIGHT/2 - wall_height/2;
	*y1 = *y0 + wall_height;
	b++;
}

void put_textures(int x, float y0, float y1, float start)
{
	unsigned int colorr;
	int *vert = g_elems.is_vertical;	
	int ray_up = g_elems.ray_angle[x] > M_PI && g_elems.ray_angle[x] < 2*M_PI;
	int ray_right = g_elems.ray_angle[x] > M_PI_2 && g_elems.ray_angle[x] < (3*M_PI) / 2;
	float pos_in_image;

	if(g_elems.is_vertical[x])
		pos_in_image = g_elems.ray_posy[x] % SQUAR_SIZE;
	else
		pos_in_image = g_elems.ray_posx[x] % SQUAR_SIZE;

	float wall_height = y1 - y0;
	float inc = SQUAR_SIZE / wall_height;
	if (start < 0)
		start = 0;
	int i = 0;
	float row = (inc * start);
	while (i < wall_height && i < HEIGHT)
	{
		if (!g_elems.is_vertical[x])
		{
			if (ray_up)
				colorr = g_elems.txtr[0].texture[SQUAR_SIZE * (int)row + (int)pos_in_image];
			if (!ray_up)
				colorr = g_elems.txtr[1].texture[SQUAR_SIZE * (int)row + (int)pos_in_image];
		}
		else if (g_elems.is_vertical[x])
		{
			if (ray_right)
				colorr = g_elems.txtr[2].texture[SQUAR_SIZE * (int)row + (int)pos_in_image];
			if (!ray_right)
				colorr = g_elems.txtr[3].texture[SQUAR_SIZE * (int)row + (int)pos_in_image];
		}
		mlx_put_pixel(image, x, y0 + i, colorr);
		row += inc;
		i++;
	}
}

void _2_to_3d()
{
	int x = 0;
	float y0;
	float y1;
	double ray_angle;
	float wall_height;
	float start = 0;

	plot_sky_and_land();
	ray_angle = (g_elems.player_a - 30*TO_RADIAN);
	while (x < WIDTH)
	{
		get_y_coordinate(&y0, &y1, g_elems.ray_distante[x], ray_angle);
		wall_height = y1 - y0;
		start = (wall_height / 2) - (HEIGHT/ 2);
		
		if(y0 > HEIGHT || y0 < 0 || y1 > HEIGHT || y1 < 0)
		{
			y0 = 0;
			y1 = HEIGHT + (start * 2);
		}
		put_textures(x, y0, y1, start);
		ray_angle += (FOV_ANGLE/RAYS_NUM);
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

void init_image()
{
	mlx = mlx_init(WIDTH, HEIGHT, "GAME", 0);
	image = mlx_new_image(mlx, WIDTH, HEIGHT);
	mlx_image_to_window(mlx, image, 0, 0);
	get_texture();
}

void plot_map()
{
	int i;

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
