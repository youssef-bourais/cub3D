/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_vertical_lines.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 11:26:28 by ybourais          #+#    #+#             */
/*   Updated: 2023/09/03 14:53:31 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_vertical_coordinate(float *x, float *y, double ray_a, int ray_r)
{
	*x = ((int)(g_inf.pos_x_p / T_SIZE)) * T_SIZE;
	if (ray_r)
		*x += T_SIZE;
	*y = g_inf.pos_y_p - ((g_inf.pos_x_p - *x) * tan(ray_a));
	if (!ray_r)
		(*x) -= (float)1 / WIDTH;
}

void	init_vertical_steps(float *delta_x, float *delta_y, double ray_angle)
{
	*delta_x = T_SIZE;
	*delta_y = T_SIZE * tan(ray_angle);
}

void	find_vertical_intersection(double ray_angle, float *x, float *y)
{
	t_coordinate	vert;

	init_direction(&vert.ray_up, &vert.ray_right, ray_angle);
	init_vertical_coordinate(&vert.n_x, &vert.n_y, ray_angle, vert.ray_right);
	init_vertical_steps(&vert.delta_x, &vert.delta_y, ray_angle);
	if ((!vert.ray_up && vert.delta_y < 0) || (vert.ray_up && vert.delta_y > 0))
		vert.delta_y *= -1;
	if (!vert.ray_right)
		vert.delta_x *= -1;
	while (vert.n_x >= 0 && vert.n_x <= g_inf.width * T_SIZE
		&& vert.n_y >= 0 && vert.n_y <= g_inf.height * T_SIZE)
	{
		if (in_map_pixel(vert.n_x, vert.n_y))
		{
			*x = vert.n_x;
			*y = vert.n_y;
			break ;
		}
		vert.n_x += vert.delta_x;
		vert.n_y += vert.delta_y;
	}
}
