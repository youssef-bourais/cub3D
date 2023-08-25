/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plotting_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourais <ybourais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 11:36:23 by ybourais          #+#    #+#             */
/*   Updated: 2023/08/25 15:38:24 by ybourais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


void draw_line(float x, float y)
{
	float new_x = cos(g_elems.player_angle)*50;
	float new_y = sin(g_elems.player_angle)*50;
	DDA(x, y, x + new_x, y + new_y, PURPLE);
}
