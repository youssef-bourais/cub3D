/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourais <ybourais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 11:17:00 by ybourais          #+#    #+#             */
/*   Updated: 2023/08/25 11:33:14 by ybourais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void rotate_player()
{
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);

	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		g_elems.player_angle = g_elems.player_angle - 2*TO_RADIAN;
		g_elems.player_angle = normalize_angle(g_elems.player_angle);
		plot_map();
		draw_player(RED, 0, 0);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		g_elems.player_angle = g_elems.player_angle + 2*TO_RADIAN;
		g_elems.player_angle = normalize_angle(g_elems.player_angle);
		plot_map();
		draw_player(RED, 0, 0);
	}
}

void update_check_plot_player(float x, float y)
{
	int move_speed;
	move_speed = 3;
	float new_x = x * move_speed;
	float new_y = y * move_speed;
	if(g_elems.map[(int)(g_elems.pos_y_p + new_y)/(SQUAR_SIZE)][(int)(g_elems.pos_x_p + new_x)/(SQUAR_SIZE)] != '1' 
		&& g_elems.map[(int)(g_elems.pos_y_p - move_speed + new_y)/(SQUAR_SIZE)][(int)(g_elems.pos_x_p + new_x)/(SQUAR_SIZE)] != '1'
		&& g_elems.map[(int)(g_elems.pos_y_p + move_speed + new_y)/(SQUAR_SIZE)][(int)(g_elems.pos_x_p + new_x)/(SQUAR_SIZE)] != '1'
		&& g_elems.map[(int)(g_elems.pos_y_p + new_y)/(SQUAR_SIZE)][(int)(g_elems.pos_x_p  - move_speed + new_x)/(SQUAR_SIZE)] != '1'
		&& g_elems.map[(int)(g_elems.pos_y_p + new_y)/(SQUAR_SIZE)][(int)(g_elems.pos_x_p - move_speed + new_x)/(SQUAR_SIZE)] != '1')
		draw_player(RED, new_x, new_y);
	else
		draw_player(RED, 0, 0);
}

void keyhook()
{
	rotate_player();
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
	{
		plot_map();
		update_check_plot_player(cos(g_elems.player_angle), sin(g_elems.player_angle));
	}
	else if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
	{
		plot_map();
		update_check_plot_player(-cos(g_elems.player_angle), -sin(g_elems.player_angle));
	}
	else if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		plot_map();
		update_check_plot_player(cos(M_PI/2 - g_elems.player_angle), -sin(M_PI/2 - g_elems.player_angle));
	}
	else if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		plot_map();
		update_check_plot_player(-cos(M_PI/2 - g_elems.player_angle), sin(M_PI/2 - g_elems.player_angle));
	}
}

double normalize_angle(double angle)
{
	if (angle < 0)
		angle += 2 * M_PI;
	if (angle >= 2 * M_PI)
    	angle -= 2 * M_PI;
	return angle;
}
