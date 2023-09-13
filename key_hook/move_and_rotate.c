/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_and_rotate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourais <ybourais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 11:17:00 by ybourais          #+#    #+#             */
/*   Updated: 2023/09/13 17:46:32 by ybourais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	rotate_player(void)
{
	if (mlx_is_key_down(g_inf.mlx, MLX_KEY_ESCAPE))
		mlx_close_window(g_inf.mlx);
	if (mlx_is_key_down(g_inf.mlx, MLX_KEY_LEFT))
	{
		g_inf.player_a = g_inf.player_a - 3 * (M_PI / (double)180);
		g_inf.player_a = normalize_angle(g_inf.player_a);
	}
	if (mlx_is_key_down(g_inf.mlx, MLX_KEY_RIGHT))
	{
		g_inf.player_a = g_inf.player_a + 3 * (M_PI / (double)180);
		g_inf.player_a = normalize_angle(g_inf.player_a);
	}
}

void	move_player(float x, float y)
{
	float	new_x;
	float	new_y;
	int		move_speed;
	int		check_x;
	int		check_y;

	move_speed = T_SIZE / 12;
	new_x = x * move_speed;
	new_y = y * move_speed;
	check_y = g_inf.pos_y_p + new_y;
	check_x = g_inf.pos_x_p + new_x;
	if (g_inf.map[check_y / T_SIZE][(check_x) / T_SIZE] != '1' 
		&& g_inf.map[(check_y - move_speed) / T_SIZE][check_x / T_SIZE] != '1'
		&& g_inf.map[(check_y + move_speed) / T_SIZE][check_x / T_SIZE] != '1'
		&& g_inf.map[check_y / T_SIZE][(check_x - move_speed) / T_SIZE] != '1'
		&& g_inf.map[check_y / T_SIZE][(check_x - move_speed) / T_SIZE] != '1')
	{
		g_inf.pos_x_p = new_x + g_inf.pos_x_p;
		g_inf.pos_y_p = new_y + g_inf.pos_y_p;
	}
}

void	keyhook(void *param)
{
	(void)param;
	rotate_player();
	if (mlx_is_key_down(g_inf.mlx, MLX_KEY_W))
		move_player(cos(g_inf.player_a), sin(g_inf.player_a));
	if (mlx_is_key_down(g_inf.mlx, MLX_KEY_S))
		move_player(-cos(g_inf.player_a), -sin(g_inf.player_a));
	if (mlx_is_key_down(g_inf.mlx, MLX_KEY_A))
		move_player(cos(M_PI / 2 - g_inf.player_a), \
		-sin(M_PI / 2 - g_inf.player_a));
	if (mlx_is_key_down(g_inf.mlx, MLX_KEY_D))
		move_player(-cos(M_PI / 2 - g_inf.player_a), \
		sin(M_PI / 2 - g_inf.player_a));
	cast_rays();
	draw_texture();
}

double	normalize_angle(double angle)
{
	if (angle < 0)
		angle += 2 * M_PI;
	if (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}
