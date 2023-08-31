/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 17:25:35 by msodor            #+#    #+#             */
/*   Updated: 2023/08/31 20:13:03 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_player_a(char *p)
{
	if (!ft_strcmp(p, "N"))
		g_inf.player_a = 3 * M_PI / 2;
	else if (!ft_strcmp(p, "S"))
		g_inf.player_a = M_PI / 2;
	else if (!ft_strcmp(p, "W"))
		g_inf.player_a = M_PI;
	else if (!ft_strcmp(p, "E"))
		g_inf.player_a = 0;
}

void	init_info(char *file)
{
	g_inf.file = file;
	g_inf.ray_distante = malloc(RAYS_NUM * sizeof(float));
	g_inf.is_vertical = malloc(RAYS_NUM * sizeof(int));
	g_inf.fd = open(g_inf.file, O_RDONLY);
	g_inf.ea = NULL;
	g_inf.no = NULL;
	g_inf.so = NULL;
	g_inf.we = NULL;
	g_inf.map = NULL;
	g_inf.player = NULL;
	g_inf.width = 0;
	g_inf.height = 0;
	g_inf.floor = 0;
	g_inf.ceiling = 0;
	g_inf.pos_x_p = 0;
	g_inf.pos_y_p = 0;
}
