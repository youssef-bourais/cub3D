/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourais <ybourais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 17:25:35 by msodor            #+#    #+#             */
/*   Updated: 2023/08/09 19:30:45 by ybourais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_info(char *file)
{
	g_elems.file = file;
	g_elems.fd = open(g_elems.file, O_RDONLY);
	g_elems.ea = NULL;
	g_elems.no = NULL;
	g_elems.so = NULL;
	g_elems.we = NULL;
	g_elems.map = NULL;
	g_elems.player = NULL;
	g_elems.width = 0;
	g_elems.height = 0;
	g_elems.floor = 0;
	g_elems.ceiling = 0;
	g_elems.player_x = 0;
	g_elems.player_y = 0;
}
