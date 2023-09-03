/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_horizontal_lines.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 11:21:41 by ybourais          #+#    #+#             */
/*   Updated: 2023/09/03 14:52:36 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_horizontal_coordinate(float *x, float *y, double ray_a, int ray_up)
{
	*y = ((int)(g_inf.pos_y_p / T_SIZE)) * T_SIZE;
	if (!ray_up)
		*y += T_SIZE;
	*x = g_inf.pos_x_p - ((g_inf.pos_y_p - *y) / tan(ray_a - M_PI));
	if (ray_up)
		(*y) -= (float)1 / HEIGHT;
}

void	init_direction(int *ray_up, int *ray_right, double ray_angle)
{
	*ray_up = ray_angle >= M_PI && ray_angle < 2 * M_PI;
	*ray_right = ray_angle >= (3 * M_PI) / 2 || ray_angle < M_PI / 2;
}

void	init_horizontal_steps(float *delta_x, float *delta_y, double ray_angle)
{
	*delta_x = T_SIZE / tan(ray_angle - M_PI);
	*delta_y = T_SIZE;
}

void	find_horizontal_intersection(double ray_angle, float *x, float *y)
{
	t_coordinate	horiz;

	init_direction(&horiz.ray_up, &horiz.ray_right, ray_angle);
	init_horizontal_coordinate(&horiz.n_x, &horiz.n_y, ray_angle, horiz.ray_up);
	init_horizontal_steps(&horiz.delta_x, &horiz.delta_y, ray_angle);
	if ((!horiz.ray_right && horiz.delta_x > 0)
		|| (horiz.ray_right && horiz.delta_x < 0))
		horiz.delta_x *= -1;
	if (horiz.ray_up)
		horiz.delta_y *= -1;
	while (horiz.n_x >= 0 && horiz.n_x <= g_inf.width * T_SIZE
		&& horiz.n_y >= 0 && horiz.n_y <= g_inf.height * T_SIZE)
	{
		if (in_map_pixel(horiz.n_x, horiz.n_y))
		{
			*x = horiz.n_x;
			*y = horiz.n_y;
			break ;
		}
		horiz.n_x += horiz.delta_x;
		horiz.n_y += horiz.delta_y;
	}
}
