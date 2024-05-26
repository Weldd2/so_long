/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amura <amura@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 11:08:26 by amura             #+#    #+#             */
/*   Updated: 2024/05/26 11:17:28 by amura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_tiles_img(t_map *map)
{
	int	y;

	y = 0;
	if (map->tiles_img != NULL)
	{
		while (map->y_l >= y)
		{
			free(map->tiles_img[y]);
			y++;
		}
		free(map->tiles_img);
	}
}

void	delete_image(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	if (map->mlx != NULL && map->tiles_img != NULL)
	{
		while (map->y_l >= y)
		{
			x = 0;
			while (map->x_l >= x)
			{
				mlx_delete_image(map->mlx, map->tiles_img[y][x]);
				x++;
			}
			y++;
		}
	}
}

void	free_tiles(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->y_l)
	{
		free(map->tiles[i]);
		i++;
	}
}

void	free_map(t_map *map)
{
	delete_image(map);
	free_tiles_img(map);
	free_tiles(map);
	free(map->tiles);
	if (map->mlx != NULL)
		mlx_terminate(map->mlx);
	free(map);
}
