/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourais <ybourais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 12:02:20 by msodor            #+#    #+#             */
/*   Updated: 2023/08/21 13:19:06 by ybourais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	checks()
{
	get_game_info();
	check_map();
	init_player_a(g_elems.player);
	check_map_closed();
	check_wals();
	if (!g_elems.ea || !g_elems.no || !g_elems.so || !g_elems.we)
		ft_err("Missing info : texturs\n");
	if (!g_elems.player)
		ft_err("Missing info : player\n");
	if (g_elems.ceiling != 1 || g_elems.floor != 1)
		ft_err("Missing info : colors\n");
}

void draw_square(uint32_t color, int x, int y)
{
	int size_x = x + SQUAR_SIZE - 1;
	int size_y = y + SQUAR_SIZE - 1;
	int firs_y = y;

	while (x < size_x)
	{
		y = firs_y;
		while (y < size_y)
		{
			mlx_put_pixel(image, x, y, color);
			y++;
		}
		x++;
	}
}

void draw_grid()
{
    int i = 0;
    while (i < g_elems.height * SQUAR_SIZE)
    {
        int j = 0;
        while (j < g_elems.width * SQUAR_SIZE)
        {
			mlx_put_pixel(image, j, i, BLACK);
            j++;
        }
        i++;
    }
}

void plot_map()
{
	int i = 0;
	int static b;

	if(b == 0)
	{
		mlx = mlx_init(SQUAR_SIZE * g_elems.width, SQUAR_SIZE * g_elems.height, "GAME", 0);
		image = mlx_new_image(mlx, SQUAR_SIZE * g_elems.width, SQUAR_SIZE * g_elems.height);
		mlx_image_to_window(mlx, image, 0, 0);
		b++;
	}
	i = 0;
	draw_grid();
	while (g_elems.map[i])
	{
		int j = 0;
		while (g_elems.map[i][j])
		{
			if(g_elems.map[i][j] == '1')
				draw_square(BLUE, (SQUAR_SIZE) * j, (SQUAR_SIZE) * i);
			else if (g_elems.map[i][j] != ' ')
				draw_square(GRAY, (SQUAR_SIZE) * j, (SQUAR_SIZE) * i);
			j++;
		}
		i++;
	}
}

void normalize_angle(double angle)
{
	if (angle < 0)
		angle += 2 * M_PI;
	if (angle >= 2 * M_PI)
    	angle -= 2 * M_PI;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

void DDA(float x0, float y0, float x1, float y1, uint32_t color)
{
	t_norm norm;
    norm.dx = x1 - x0;
    norm.dy = y1 - y0;
	int steps;

	if (abs(norm.dx) >= abs(norm.dy))
		steps = abs(norm.dx);
	else
		steps = abs(norm.dy);
    norm.x = x0;
    norm.y = y0;
	norm.x_step = (float)norm.dx / steps;
	norm.y_step = (float)norm.dy / steps;
	int i = 0;
	while (i <= steps)
	{
		int xx = round(norm.x);
		int yy = round(norm.y);
		if(g_elems.map[yy/SQUAR_SIZE][xx/SQUAR_SIZE] != '1')
		{
			mlx_put_pixel(image, round(norm.x), round(norm.y), color);
		}
		if(g_elems.map[yy/SQUAR_SIZE][xx/SQUAR_SIZE] == '1' 
			|| g_elems.map[(yy + 1)/SQUAR_SIZE][xx/SQUAR_SIZE] == '1' 
			|| g_elems.map[(yy - 1)/SQUAR_SIZE][xx/SQUAR_SIZE] == '1' 
			|| g_elems.map[yy/SQUAR_SIZE][(xx + 1)/SQUAR_SIZE] == '1' 
			|| g_elems.map[yy/SQUAR_SIZE][(xx - 1)/SQUAR_SIZE] == '1')
			break;
		norm.x = norm.x + norm.x_step;
		norm.y = norm.y + norm.y_step;
		i++;
	}
}

int in_map_pixel(int x, int y)
{
	int new_x = x/SQUAR_SIZE;
	int new_y = y/SQUAR_SIZE;

	int i = 0;
	while (i < g_elems.width)
	{
		int j = 0;
		while (j < g_elems.height)
		{
			if (i == new_x && j == new_y)
				return 1;
			j++;
		}
		i++;
	}
	return 0;
}

void creat_ray(float x, float y, double ray_angle)
{
	float new_x = cos(ray_angle)*500;//
	float new_y = sin(ray_angle)*500;//
	DDA(x, y, x + new_x, y + new_y, CYAN);
}

// void cast_one_ray(float x, float y, double ray_angle)
// {
	
// }

void	cast_rays(float x, float y)
{
	double ray_angle = g_elems.player_angle - (FOV_ANGLE/2);
	int i = 0;
	while (i < RAYS_NUM)
	{
		creat_ray(x, y, ray_angle);
		// cast_one_ray(x, y, ray_angle);
		ray_angle = ray_angle + (FOV_ANGLE/RAYS_NUM);
		// normalize_angle(ray_angle);
		i++;
	}
}

void draw_line(float x, float y)
{
	float new_x = cos(g_elems.player_angle)*100;
	float new_y = sin(g_elems.player_angle)*100;
	DDA(x, y, x + new_x, y + new_y, PURPLE);
}

void draw_player(uint32_t color, float x, float y)
{
	g_elems.pos_x_p = x + g_elems.pos_x_p;
	g_elems.pos_y_p = y + g_elems.pos_y_p;
	x = g_elems.pos_x_p;
	y = g_elems.pos_y_p;

	int radius = PLAYER_SIZE / 2;
	int pixel_x = x - radius;
	cast_rays(x, y);
	draw_line(x, y);
	while (pixel_x < x + radius)
    {
		int pixel_y = y - radius;
        while (pixel_y <= y + radius)
        {
            if (pow(pixel_x - x, 2) + pow(pixel_y - y, 2) <= pow(radius, 2))
                mlx_put_pixel(image, pixel_x, pixel_y, RED);
			pixel_y++;
        }
		pixel_x++;
    }
	(void)color;
}

void rotate_player()
{
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		g_elems.player_angle = g_elems.player_angle - 3*M_PI/(double)180;
		plot_map();
		draw_player(BLUE, 0, 0);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		g_elems.player_angle = g_elems.player_angle + 3*M_PI/(double)180;
		plot_map();
		draw_player(BLUE, 0, 0);
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
		draw_player(BLUE, new_x, new_y);
	else
		draw_player(BLUE, 0, 0);
}

void keyhook()
{
	normalize_angle(g_elems.player_angle);
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

int	main(int ac, char **av)
{
	if (ac != 2)
		ft_err("Wrong number of arguments\n");
	init_info(av[1]);
	checks();
	plot_map();
	draw_player(BLUE, 0, 0);
	printf("%d %d \n",g_elems.width*SQUAR_SIZE, g_elems.height*SQUAR_SIZE);
	mlx_loop_hook(mlx, keyhook, NULL);
	mlx_loop(mlx);
}
