/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:21:19 by msodor            #+#    #+#             */
/*   Updated: 2023/08/03 18:30:44 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int check_map(t_elems *elem)
{
	int i;
	int j;

	i = 0;
	while (elem->map[i])
	{
		j = 0;
		while (elem->map[i][j])
		{
			if (elem->map[i][j] != '1' && elem->map[i][j] != '0' \
			&& elem->map[i][j] != ' ' && elem->map[i][j] != 'N' \
			&& elem->map[i][j] != 'S' && elem->map[i][j] != 'W' \
			&& elem->map[i][j] != 'E')
				return 1;
			j++;
		}
		i++;
	}
	return 0;
}
