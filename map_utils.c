/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 11:24:07 by antoinemura       #+#    #+#             */
/*   Updated: 2024/04/06 21:33:46 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	iterate_map(t_map *map, int func(t_map *, int, int))
{
	int	y;
	int	x;

	y = 0;
	while (y < map->y_l)
	{
		x = 0;
		while (x < map->x_l)
		{
			if (!func(map, y, x))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}
