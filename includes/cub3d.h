/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 14:49:17 by msodor            #+#    #+#             */
/*   Updated: 2023/08/02 15:29:23 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 29
# endif

#define WIDTH 1280
#define HEIGHT 720

# include "../MLX42/MLX42.h"
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <string.h>

static	mlx_image_t* image;
int			ft_strlen(char *str);
int			ft_strchr(char *str, char c);
char		*ft_strjoin(char *s1, char *s2);
char		*get_next_line(int fd);

typedef struct s_map
{
	char	*file;
	int		fd;
	// int		file_lines;
	char	**map;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		*floor;
	int		*ceiling;
}				t_map;

#endif