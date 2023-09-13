/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourais <ybourais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 14:49:17 by msodor            #+#    #+#             */
/*   Updated: 2023/09/13 17:53:12 by ybourais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 310
# endif

# include "../MLX42/MLX42.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define WIDTH 1400
# define HEIGHT 1200

# define T_SIZE 64
# define PLAYER_SIZE 10
# define RAY_WIDTH 1
# define RAYS_NUM 1400

typedef struct s_txtr
{
	int				width;
	int				height;
	uint32_t		*texture;
}					t_txtr;

typedef struct s_elems
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_txtr		txtr[4];
	float		x;
	float		y;
	char		*file;
	int			fd;
	int			width;
	int			height;
	char		**map;
	char		*player;
	int			player_x;
	int			player_y;
	double		player_a;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	int			floor;
	int			ceiling;
	float		pos_x_p;
	float		pos_y_p;
	float		*ray_distante;
	int			*is_vertical;
	int			f_color[3];
	int			c_color[3];
	int			ray_posx[WIDTH];
	int			ray_posy[WIDTH];
	float		ray_angle[WIDTH];
}					t_elems;

t_elems	g_inf;

typedef struct s_coordinate
{
	int				ray_up;
	int				ray_right;
	float			n_x;
	float			n_y;
	float			delta_y;
	float			delta_x;
}					t_coordinate;

typedef struct s_norm
{
	int				dx;
	int				dy;
	int				steps;
	float			x;
	float			y;
	float			x_step;
	float			y_step;
	float			slope;
}					t_norm;

typedef struct s_data
{
	float			x;
	float			y;
}					t_data;

typedef struct s_direction
{
	int				up;
	int				down;
	int				right;
	int				left;
}					t_direction;

/*========================================*/

void	get_texture(void);
void	width_height(void);
void	check_map_size(void);
void	init_image(void);
void	plot_sky_and_land(void);
void	draw_texture(void);
/*========================================*/
/*===============ray_casting==============*/
/*========================================*/
/*ray_casting*/
void	cast_rays(void);
void	creat_ray(double ray_angle, float *dst, int *is_vertical);
float	distance(float x1, float y1, float x2, float y2);
t_data	compare_distance(float x_v, float y_v, float x_h, float y_h);
int		in_map_pixel(float x, float y);
/*cast_horizontal_lines*/
void	init_direction(int *ray_up, int *ray_right, double ray_angle);
void	init_horizontal_steps(float *delta_x, float *delta_y, double ray_angle);
void	find_horizontal_intersection(double ray_angle, float *x, float *y);
/*cast_vertical_lines*/
void	init_vertical_steps(float *delta_x, float *delta_y, double ray_angle);
void	find_vertical_intersection(double ray_angle, float *x, float *y);
/*=====================================*/
/*===============key_hook==============*/
/*=====================================*/
/*move_and_rotate*/
void	rotate_player(void);
void	move_player(float x, float y);
void	keyhook(void *param);
double	normalize_angle(double angle);
int32_t	ft_pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

/*=====================================*/
/*===============plot==================*/
/*=====================================*/
/*tools*/
void	init_player_a(char *p);
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
void	get_game_info(void);
int		check_map(void);
int		check_map_closed(void);
int		check_wals(void);
void	separated_map(char *one_line_map);
void	set_f_color(char **info);
void	set_c_color(char **info);
int		is_rgb(int nbr);
int		is_unmber(char *str);
void	ft_err(char *str);
int		is_map_comp(char c);
int		is_player(char c);
void	get_y_coordinate(float *y0, float *y1, float distance, double ray_a);
void	plot_sky_and_land(void);
void	cleanup(void);
void	cleanup_err(void);
int		count_coma(char *str);

#endif
