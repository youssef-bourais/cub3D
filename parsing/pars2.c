/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elems_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:15:19 by msodor            #+#    #+#             */
/*   Updated: 2023/08/31 15:20:24 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	is_unmber(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	is_rgb(int nbr)
{
	if (nbr < 0 || nbr > 255)
		return (1);
	return (0);
}

void	set_f_color(char **info)
{
	char	**rgb;

	rgb = ft_split(info[1], ",");
	if (!rgb[0] || !rgb[1] || !rgb[2])
	{
		free_array(rgb);
		ft_err("RGB colors must have 3 values\n");
	}
	if (is_unmber(rgb[0]) || is_unmber(rgb[1]) || is_unmber(rgb[2]))
	{
		free_array(rgb);
		ft_err("RGB vlue must be a proper number\n");
	}
	g_elems.f_color[0] = ft_atoi(rgb[0]);
	g_elems.f_color[1] = ft_atoi(rgb[1]);
	g_elems.f_color[2] = ft_atoi(rgb[2]);
	g_elems.floor += 1;
	if (is_rgb(g_elems.f_color[0]) || is_rgb(g_elems.f_color[1]) \
	|| is_rgb(g_elems.f_color[2]))
	{
		free_array(rgb);
		ft_err("RGB vlue must be between 0 and 255\n");
	}
	free_array(rgb);
}

void	set_c_color(char **info)
{
	char	**rgb;

	rgb = ft_split(info[1], ",");
	if (!rgb[0] || !rgb[1] || !rgb[2])
	{
		free_array(rgb);
		ft_err("RGB colors must have 3 values\n");
	}
	if (is_unmber(rgb[0]) || is_unmber(rgb[1]) || is_unmber(rgb[2]))
	{
		free_array(rgb);
		ft_err("RGB vlue must be a proper number\n");
	}
	g_elems.c_color[0] = ft_atoi(rgb[0]);
	g_elems.c_color[1] = ft_atoi(rgb[1]);
	g_elems.c_color[2] = ft_atoi(rgb[2]);
	g_elems.ceiling += 1;
	if (is_rgb(g_elems.c_color[0]) || is_rgb(g_elems.c_color[1]) \
	|| is_rgb(g_elems.c_color[2]))
	{
		free_array(rgb);
		ft_err("RGB vlue must be between 0 and 255\n");
	}
	free_array(rgb);
}
