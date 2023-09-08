/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 12:02:20 by msodor            #+#    #+#             */
/*   Updated: 2023/09/08 11:55:03 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	checks(void)
{
	get_game_info();
	width_height();
	check_map();
	init_player_a(g_inf.player);
	check_map_closed();
	check_wals();
	if (!g_inf.ea || !g_inf.no || !g_inf.so || !g_inf.we)
		ft_err("Missing info : texturs\n");
	if (!g_inf.player)
		ft_err("Missing info : player\n");
	if (g_inf.ceiling != 1 || g_inf.floor != 1)
		ft_err("Missing info : colors\n");
}

int	main(int ac, char **av)
{
	if (ac != 2)
		ft_err("Wrong number of arguments\n");
	init_info(av[1]);
	checks();
	init_image();
	mlx_loop_hook(g_inf.mlx, keyhook, NULL);
	mlx_loop(g_inf.mlx);
}
