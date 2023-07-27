/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 12:02:20 by msodor            #+#    #+#             */
/*   Updated: 2023/07/27 17:50:44 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

// -----------------------------------------------------------------------------

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
  return (r << 24 | g << 16 | b << 8 | a);
}

void ft_randomize(void* param)
{
	(void)param;
	for (uint32_t i = 0; i < image->width; ++i)
	{
		for (uint32_t y = 0; y < image->height; ++y)
		{
			uint32_t color = ft_pixel(0xFF, 0xFF, 0xFF, 0xFF);
			mlx_put_pixel(image, i, y, color);
		}
	}
}

void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		image->instances[0].y -= 2;
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		image->instances[0].y += 2;
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		image->instances[0].x -= 2;
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		image->instances[0].x += 2;
}


// -----------------------------------------------------------------------------

int32_t main()
{
	mlx_t* mlx;

	mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", 0);

	image = mlx_new_image(mlx, 5, 5);

	mlx_image_to_window(mlx, image, 0, 0);
	
	mlx_loop_hook(mlx, ft_randomize, mlx);
	mlx_loop_hook(mlx, ft_hook, mlx);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

