/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 11:22:34 by ybourais          #+#    #+#             */
/*   Updated: 2023/08/31 20:13:03 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


void	cast_rays()
{
	double ray_angle = g_inf.player_a - (FOV_ANGLE/2);
	int i = 0;
	int is_vertical;
	float distance;
	while (i < RAYS_NUM)
	{
		ray_angle = normalize_angle(ray_angle);
		creat_ray(ray_angle, &distance, &is_vertical);
		g_inf.ray_distante[i] = distance;
		g_inf.is_vertical[i] = is_vertical;
		ray_angle = ray_angle + (FOV_ANGLE/RAYS_NUM);
		g_inf.ray_angle[i] = ray_angle;
		g_inf.ray_posx[i] = g_inf.x;
		g_inf.ray_posy[i] = g_inf.y;
		i++;
	}
}

void creat_ray(double ray_angle, float *dst, int *is_vertical)
{
	t_data horizontal;
	horizontal.x_pixel = 0;
	horizontal.y_pixel = 0;

	t_data vertical;
	vertical.x_pixel = 0;
	vertical.y_pixel = 0;

	t_data short_distance;
	short_distance.x_pixel = 0;
	short_distance.y_pixel = 0;
	find_horizontal_intersection(ray_angle, &horizontal.x_pixel, &horizontal.y_pixel);
	find_vertical_intersection(ray_angle, &vertical.x_pixel, &vertical.y_pixel);
	short_distance = compare_distance(vertical.x_pixel, vertical.y_pixel, horizontal.x_pixel, horizontal.y_pixel);
	*is_vertical = (short_distance.x_pixel == vertical.x_pixel);
	g_inf.x = short_distance.x_pixel;
	g_inf.y = short_distance.y_pixel;
	
	*dst = distance(g_inf.pos_x_p, g_inf.pos_y_p, short_distance.x_pixel, short_distance.y_pixel);
}

float distance(float x1, float y1, float x2, float y2)
{
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

t_data compare_distance(float x_v, float y_v, float x_h, float y_h)
{
	float horiz_dis;
	float vert_dis;

	if (x_h)
		horiz_dis = distance(g_inf.pos_x_p, g_inf.pos_y_p, x_h, y_h);
	else
		horiz_dis = INT_MAX;
	if (x_v)
		vert_dis = distance(g_inf.pos_x_p, g_inf.pos_y_p, x_v, y_v);
	else
		vert_dis = INT_MAX;
	if (horiz_dis < vert_dis)
		return (t_data){x_h, y_h};
	else
		return (t_data){x_v, y_v};
}

int	in_map_pixel(float x, float y)
{
	int lenx;
	int new_x = x/T_SIZE;
	int new_y = y/T_SIZE;

	if (new_y >= g_inf.height)
		return 1;
	lenx = ft_strlen(g_inf.map[new_y]);
	if (new_x < 0 || new_x >= lenx || new_y < 0 || new_y >= g_inf.height)
		return 1;
	if (g_inf.map[new_y][new_x] == '1')
		return 1;
	return 0;
}