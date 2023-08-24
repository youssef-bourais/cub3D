/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourais <ybourais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 14:49:17 by msodor            #+#    #+#             */
/*   Updated: 2023/08/24 11:23:15 by ybourais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 29
# endif

# include "../MLX42/MLX42.h"
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <string.h>

# define WIDTH 2050
# define HEIGHT 750

# define SQUAR_SIZE 50
# define PLAYER_SIZE 16
# define RAY_WIDTH 1
# define RAYS_NUM (WIDTH/RAY_WIDTH)
# define TO_RADIAN (M_PI/(double)180)
# define FOV_ANGLE (60*TO_RADIAN)


#define WHITE 0xFFFFFFFF
#define BLUE 0xFFFF
#define RED 0xFF0000FF
#define PURPLE 0xFF00FFFF
#define YELLOW 0xFFFF00FF
#define BLACK 0x00000000

#define GREEN 0x00FF00FF
#define ORANGE 0xFFA500FF
#define PINK 0xFF69B4FF
#define CYAN 0x00FFFFFF
#define GRAY 0x808080FF
#define BROWN 0xA52A2AFF

mlx_t* mlx;
static	mlx_image_t* image;

typedef struct s_elems
{
	char	*file;
	int		fd;
	int		width;
	int		height;
	char	**map;
	char	*player;
	int		player_x;
	int		player_y;
	double	player_angle;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		floor;
	int		ceiling;
	float	pos_x_p;
	float	pos_y_p;
	int		f_color[3];
	int		c_color[3];
}	t_elems;
t_elems g_elems;

typedef struct s_norm
{
	int dx;
	int dy;
	int steps;
	float x;
	float y;
	float x_step;
	float y_step;
	float slope;
}	t_norm;

typedef struct s_data
{
	float x_pixel;
	float y_pixel;
}	t_data;

typedef struct s_direction
{
	int up;
	int down;
	int right;
	int left;
}	t_direction;

/*tools*/
void init_player_a(char *p);
int		ft_atoi(const char *str);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strchr(const char *str, int c);
int		ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, unsigned int n);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char *c);
char	*ft_strdup(const char *s1);
char	*ft_itoa(int n);
/*-------------------------*/

int		f_strlen(char *str);
int		f_strchr(char *str, char c);
char	*f_strjoin(char *s1, char *s2);
char	*get_next_line(int fd);
void	init_info(char *file);
void	free_array(char **array);
void	set_info(char **info);
void	get_game_info();
int		check_map();
int		check_map_closed();
int		check_wals();
void	ft_err(char *str);
void	ft_err(char *str);

#endif
