/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 11:06:56 by ybourais          #+#    #+#             */
/*   Updated: 2023/09/08 11:58:31 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	plot_sky_and_land(void)
{
	int			i;
	int			j;
	u_int32_t	floor;
	u_int32_t	sky;

	i = 0;
	floor = ft_pixel(g_inf.f_color[0], g_inf.f_color[1], g_inf.f_color[2], 225);
	sky = ft_pixel(g_inf.c_color[0], g_inf.c_color[1], g_inf.c_color[2], 225);
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			if (i <= HEIGHT / 2)
				mlx_put_pixel(g_inf.image, j, i, sky);
			else
				mlx_put_pixel(g_inf.image, j, i, floor);
			j++;
		}
		i++;
	}
}

unsigned int	getc_color(float row, float col, int x)
{
	int	ray_u;
	int	ray_r;

	ray_u = g_inf.ray_angle[x] > M_PI && g_inf.ray_angle[x] < 2 * M_PI;
	ray_r = g_inf.ray_angle[x] > M_PI_2 && g_inf.ray_angle[x] < (3 * M_PI) / 2;
	if (!g_inf.is_vertical[x])
	{
		if (ray_u)
			return (g_inf.txtr[0].texture[T_SIZE * (int)row + (int)col]);
		if (!ray_u)
			return (g_inf.txtr[1].texture[T_SIZE * (int)row + (int)col]);
	}
	else if (g_inf.is_vertical[x])
	{
		if (ray_r)
			return (g_inf.txtr[2].texture[T_SIZE * (int)row + (int)col]);
		if (!ray_r)
			return (g_inf.txtr[3].texture[T_SIZE * (int)row + (int)col]);
	}
	return (0);
}

void	put_textures(int x, float y0, float y1, float start)
{
	float			col;
	float			row;
	float			wall_height;
	float			inc;
	int				i;

	if (g_inf.is_vertical[x])
		col = g_inf.ray_posy[x] % T_SIZE;
	else
		col = g_inf.ray_posx[x] % T_SIZE;
	wall_height = y1 - y0;
	inc = T_SIZE / wall_height;
	if (start < 0)
		start = 0;
	i = 0;
	row = (inc * start);
	while (i < wall_height && i < HEIGHT)
	{
		mlx_put_pixel(g_inf.image, x, y0 + i, getc_color(row, col, x));
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
		start = (wall_height / 2) - (HEIGHT / 2);
		if (y0 > HEIGHT || y0 < 0 || y1 > HEIGHT || y1 < 0)
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
	g_inf.mlx = mlx_init(WIDTH, HEIGHT, "GAME", 0);
	g_inf.image = mlx_new_image(g_inf.mlx, WIDTH, HEIGHT);
	mlx_image_to_window(g_inf.mlx, g_inf.image, 0, 0);
	get_texture();
}
