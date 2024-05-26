/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resoudre2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amura <amura@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 21:46:11 by antoinemura       #+#    #+#             */
/*   Updated: 2024/05/26 11:06:09 by amura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**read_map(char *file_path, int y_l)
{
	char	*line;
	char	**map;
	int		y;
	int		map_fd;

	map_fd = open_map(file_path);
	if (!map_fd)
		return (0);
	map = malloc(sizeof(char *) * (y_l + 1));
	if (!map)
		return (NULL);
	line = ft_get_next_line(map_fd);
	y = 0;
	while (line)
	{
		map[y] = ft_strdup(line);
		free(line);
		line = ft_get_next_line(map_fd);
		y++;
	}
	free(line);
	return (map);
}

int	reset_map_tile_value(t_map *m, int y, int x)
{
	if (m->tiles[y][x] == '2')
		m->tiles[y][x] = '0';
	return (1);
}

int	is_valid_move(t_map *m, int new_y, int new_x)
{
	char	tile;

	if (new_y < 0 || new_x < 0 || new_y >= m->y_l || new_x >= m->x_l)
		return (0);
	tile = m->tiles[new_y][new_x];
	if (tile == '1' || tile == '2')
		return (0);
	if (tile == 'E' && m->c_count != 0)
		return (0);
	return (1);
}

int	est_resoluble(t_map *map)
{
	t_map	*map_cpy;
	mlx_t	*mlx;
	char	**tiles_cpy;
	int		i;

	tiles_cpy = malloc(sizeof(char *) * (map->y_l + 1));
	i = -1;
	while (++i < map->y_l)
		tiles_cpy[i] = ft_strdup(map->tiles[i]);
	map_cpy = init_map(tiles_cpy, map->y_l, map->x_l);
	mlx = NULL;
	map_cpy->mlx = mlx;
	map_cpy->p_x = map->p_x;
	map_cpy->p_y = map->p_y;
	map_cpy->p_count = map->p_count;
	map_cpy->c_count = map->c_count;
	map_cpy->e_count = map->e_count;
	i = resoudre(map_cpy);
	free_map(map_cpy);
	return (i);
}
