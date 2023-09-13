/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_game_info.c                                     :+:      :+: 	:+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:31:09 by msodor            #+#    #+#             */
/*   Updated: 2023/08/03 10:27:22 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_map(void)
{
	int	i;
	int	j;

	i = 0;
	while (g_inf.map[i])
	{
		j = 0;
		while (g_inf.map[i][j])
		{
			if (!is_map_comp(g_inf.map[i][j])
				&& !is_player(g_inf.map[i][j]))
				ft_err("Invalid map\n");
			if (is_player(g_inf.map[i][j]))
			{
				if (g_inf.player)
					ft_err("Duplicate player\n");
				g_inf.pos_x_p = (j * T_SIZE) + T_SIZE / 2;
				g_inf.pos_y_p = (i * T_SIZE) + T_SIZE / 2;
				g_inf.player = ft_substr(g_inf.map[i], j, 1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_l_r_wall(void)
{
	int	i;

	i = 0;
	while (g_inf.map[i])
	{
		if (g_inf.map[i][0] != '1' && g_inf.map[i][0] != ' ')
			return (1);
		i++;
	}
	i = 0;
	while (g_inf.map[i])
	{
		if (g_inf.map[i][ft_strlen(g_inf.map[i]) - 1] != '1' \
		&& g_inf.map[i][ft_strlen(g_inf.map[i]) - 1] != ' ')
			return (1);
		i++;
	}
	return (0);
}

int	check_t_b_wall(void)
{
	int	i;
	int	j;

	j = 0;
	while (g_inf.map[0][j])
	{
		if (g_inf.map[0][j] != '1' && g_inf.map[0][j] != ' ')
			return (1);
		j++;
	}
	i = 0;
	while (g_inf.map[g_inf.height - 1][i])
	{
		if (g_inf.map[g_inf.height - 1][i] != '1' \
		&& g_inf.map[g_inf.height - 1][i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

int	check_wals(void)
{
	if (check_l_r_wall() || check_t_b_wall())
		ft_err("map is not closed\n");
	return (0);
}
