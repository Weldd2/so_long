/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_structure.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amura <amura@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 11:31:30 by antoinemura       #+#    #+#             */
/*   Updated: 2024/04/13 15:48:05 by amura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_tiles_img(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	map->tiles_img = malloc(sizeof(mlx_image_t **) * (map->y_l + 1));
	while (map->y_l >= y)
	{
		map->tiles_img[y] = malloc(sizeof(mlx_image_t *) * (map->x_l + 1));
		x = 0;
		while (map->x_l >= x)
		{
			map->tiles_img[y][x] = NULL;
			x++;
		}
		y++;
	}
}

void	free_tiles_img(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	if (map->tiles_img != NULL && map->mlx != NULL)
	{
		while (map->y_l >= y)
		{
			x = 0;
			while (map->x_l >= x)
			{
				mlx_delete_image(map->mlx, map->tiles_img[y][x]);
				x++;
			}
			free(map->tiles_img[y]);
			y++;
		}
		free(map->tiles_img);
	}
}

void	fill_map(t_map *map, mlx_t *mlx)
{
	int				y;
	int				x;
	mlx_texture_t	*texture;
	mlx_image_t		*img;

	y = 0;
	while (y < map->y_l)
	{
		x = 0;
		while (x < map->x_l)
		{
			put_image(x, y, map, mlx);
			x++;
		}
		y++;
	}
	texture = mlx_load_png("./assets/tnt.png");
	img = mlx_texture_to_image(mlx, texture);
	map->tiles_img[map->p_y][map->p_x] = img;
	mlx_image_to_window(mlx, img, map->p_x * 32, map->p_y * 32);
	mlx_delete_texture(texture);
}

t_map	*init_map(char **tiles, int y_l, int x_l, int graph)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	map->tiles = tiles;
	map->x_l = x_l;
	map->y_l = y_l;
	map->tiles_img = NULL;
	map->mlx = NULL;
	if (graph)
		init_tiles_img(map);
	map->c_count = 0;
	map->e_count = 0;
	map->p_count = 0;
	return (map);
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->y_l)
	{
		free(map->tiles[i]);
		i++;
	}
	free(map->tiles);
	free(map);
}
