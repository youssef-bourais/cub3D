/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 14:49:17 by msodor            #+#    #+#             */
/*   Updated: 2023/07/26 15:49:42 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 29
# endif

# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>

int		ft_strlen(char *str);
int		ft_strchr(char *str, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*get_next_line(int fd);

typedef struct s_map
{
	char	**map;
	int		map_x;
	int		map_y;
}				t_map;

#endif