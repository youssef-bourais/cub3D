/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plotting_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 11:36:23 by ybourais          #+#    #+#             */
/*   Updated: 2023/08/31 20:28:36 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_y_coordinate(float *y0, float *y1, float distance, double ray_angle)
{
	float	wall_height;

	distance = distance * cos(g_inf.player_a - ray_angle);
	wall_height = (T_SIZE * HEIGHT) / distance;
	*y0 = HEIGHT / 2 - wall_height / 2;
	*y1 = *y0 + wall_height;
}

