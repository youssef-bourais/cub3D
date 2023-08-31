/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:21:19 by msodor            #+#    #+#             */
/*   Updated: 2023/08/31 15:14:05 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	check_map_size(void)
{
	if (g_elems.height * SQUAR_SIZE > HEIGHT / 4
		|| g_elems.width * SQUAR_SIZE > WIDTH / 3)
		ft_err("Map is too big\n");
}
