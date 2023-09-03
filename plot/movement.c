/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 11:06:56 by ybourais          #+#    #+#             */
/*   Updated: 2023/09/03 13:37:52 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	plot_sky_and_land(void)
{
	int	i;
	int	j;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			if (i <= HEIGHT / 2)
				mlx_put_pixel(image, j, i, DARK_BLUE);
			else
				mlx_put_pixel(image, j, i, DARK_GREEN);
			j++;
		}
		i++;
	}
}

void	put_textures(int x, float y0, float y1, float start)
{
	unsigned int	color;
	int ray_up = g_inf.ray_angle[x] > M_PI && g_inf.ray_angle[x] < 2*M_PI;
	int ray_right = g_inf.ray_angle[x] > M_PI_2 && g_inf.ray_angle[x] < (3*M_PI) / 2;
	float col;

	if(g_inf.is_vertical[x])
		col = g_inf.ray_posy[x] % T_SIZE;
	else
		col = g_inf.ray_posx[x] % T_SIZE;

	float wall_height = y1 - y0;
	float inc = T_SIZE / wall_height;
	if (start < 0)
		start = 0;
	int i = 0;
	float row = (inc * start);
	while (i < wall_height && i < HEIGHT)
	{
		if (!g_inf.is_vertical[x])
		{
			if (ray_up)
				color = g_inf.txtr[0].texture[T_SIZE * (int)row + (int)col];
			if (!ray_up)
				color = g_inf.txtr[1].texture[T_SIZE * (int)row + (int)col];
		}
		else if (g_inf.is_vertical[x])
		{
			if (ray_right)
				color = g_inf.txtr[2].texture[T_SIZE * (int)row + (int)col];
			if (!ray_right)
				color = g_inf.txtr[3].texture[T_SIZE * (int)row + (int)col];
		}
		mlx_put_pixel(image, x, y0 + i, color);
		row += inc;
		i++;
	}
}

void	draw_texture(void)
{
	int		x;
	float	y0;
	float	y1;
	float	wall_height;
	float	start;

	x = 0;
	start = 0;
	plot_sky_and_land();
	while (x < WIDTH)
	{
		get_y_coordinate(&y0, &y1, g_inf.ray_distante[x], g_inf.ray_angle[x]);
		wall_height = y1 - y0;
		start = (wall_height / 2) - (HEIGHT/ 2);
		if(y0 > HEIGHT || y0 < 0 || y1 > HEIGHT || y1 < 0)
		{
			y0 = 0;
			y1 = HEIGHT + (start * 2);
		}
		put_textures(x, y0, y1, start);
		x++;
	}
}

void	init_image(void)
{
	mlx = mlx_init(WIDTH, HEIGHT, "GAME", 0);
	image = mlx_new_image(mlx, WIDTH, HEIGHT);
	mlx_image_to_window(mlx, image, 0, 0);
	get_texture();
}
