/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_err.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourais <ybourais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:27:43 by msodor            #+#    #+#             */
/*   Updated: 2023/09/13 17:50:22 by ybourais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	cleanup(void)
{
	int	i;

	i = 0;
	free(g_inf.ray_distante);
	free(g_inf.is_vertical);
	free(g_inf.ea);
	free(g_inf.so);
	free(g_inf.we);
	free(g_inf.no);
	free(g_inf.player);
	free_array(g_inf.map);
	while (i < 4)
	{
		free(g_inf.txtr[i].texture);
		i++;
	}
}

void	cleanup_err(void)
{

	free(g_inf.ray_distante);
	free(g_inf.is_vertical);
}

void	ft_err(char *str)
{
	write(2, "Error\n", 6);
	write(2, str, ft_strlen(str));
	cleanup_err();
	exit(1);
}

int	count_coma(char *str)
{
	int	i;
	int	coma_count;

	i = 0;
	coma_count = 0;
	while (str[i])
	{
		if (str[i] == ',')
			coma_count++;
		i++;
	}
	if (coma_count != 2)
		return (1);
	return (0);
}
