/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_vertical_lines.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 11:26:28 by ybourais          #+#    #+#             */
/*   Updated: 2023/08/31 20:13:03 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void init_vertical_coordinate(float *x, float *y, double ray_angle, int ray_right)
{
	*x = (int)(g_inf.pos_x_p/T_SIZE)*T_SIZE;
	if(ray_right)
		*x += T_SIZE;
	*y = g_inf.pos_y_p - ((g_inf.pos_x_p - *x)*tan(ray_angle));
	if(!ray_right)
		(*x) -= (float)1/WIDTH;
}

void init_vertical_steps(float *delta_x, float *delta_y, double ray_angle)
{
	*delta_x = T_SIZE;
	*delta_y = (T_SIZE)*tan(ray_angle);
}

void find_vertical_intersection(double ray_angle, float *x, float *y)
{
	t_coordinate vertical;
	init_direction(&vertical.ray_up, &vertical.ray_right, ray_angle);
	init_vertical_coordinate(&vertical.n_x, &vertical.n_y, ray_angle, vertical.ray_right);
	init_vertical_steps(&vertical.delta_x, &vertical.delta_y, ray_angle);

	if((!vertical.ray_up && vertical.delta_y < 0) || (vertical.ray_up && vertical.delta_y > 0))
		vertical.delta_y *= -1;
	if(!vertical.ray_right)
		vertical.delta_x *= -1;

	while (vertical.n_x >= 0 
		&& vertical.n_x <= g_inf.width*T_SIZE
		&& vertical.n_y >= 0 
		&& vertical.n_y <= g_inf.height*T_SIZE)
	{
		if (in_map_pixel(vertical.n_x, vertical.n_y))
		{
			*x = vertical.n_x;
			*y = vertical.n_y;
			break;
		}
		vertical.n_x += vertical.delta_x;
		vertical.n_y += vertical.delta_y;
	}
}
