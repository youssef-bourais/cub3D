/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 14:49:17 by msodor            #+#    #+#             */
/*   Updated: 2023/08/03 15:11:11 by msodor           ###   ########.fr       */
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

typedef struct s_elems
{
	char	*file;
	int		fd;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		floor[3];
	int		ceiling[3];
}				t_elems;

/*tools*/
int		ft_atoi(const char *str);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strchr(const char *str, int c);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, unsigned int n);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char *c);
char	*ft_strdup(const char *s1);
char	*ft_itoa(int n);
/*-------------------------*/

static	mlx_image_t* image;
int		f_strlen(char *str);
int		f_strchr(char *str, char c);
char	*f_strjoin(char *s1, char *s2);
char	*get_next_line(int fd);
void	init_info(t_elems *map, char *file);
void	free_array(char **array);
int		set_info(t_elems *map, char **info);
void	get_game_info(t_elems *map);
#endif