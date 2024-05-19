/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amura <amura@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 00:22:27 by antoinemura       #+#    #+#             */
/*   Updated: 2024/04/07 03:14:02 by amura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	open_map(char	*file_path)
{
	int	map;

	map = open(file_path, O_RDONLY);
	if (map < 0)
		return (0);
	return (map);
}

int	check_line_l(char *line, int x_l)
{
	int	line_l;

	line_l = ft_strlen(line);
	if (line[line_l - 1] == '\n')
		line_l--;
	return (line_l == x_l);
}

int	est_rectangulaire(char	*file_path, int *y_l, int *x_l)
{
	int		map;
	char	*line;

	*y_l = 0;
	*x_l = 0;
	map = open_map(file_path);
	if (map == 0)
		return (0);
	line = ft_get_next_line(map);
	*x_l = (int)ft_strlen(line) - 1;
	while (line)
	{
		(*y_l)++;
		if (!check_line_l(line, *x_l))
		{
			free(line);
			return (0);
		}
		free(line);
		line = ft_get_next_line(map);
	}
	free(line);
	close(map);
	return (1);
}

int	est_map_fermee(t_map *map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < map->x_l)
	{
		if (map->tiles[0][x] != '1' || map->tiles[map->y_l - 1][x] != '1')
			return (0);
		x++;
	}
	while (y < map->y_l)
	{
		if (map->tiles[y][0] != '1' || map->tiles[y][map->x_l - 1] != '1')
			return (0);
		y++;
	}
	return (1);
}

int	compteur_speciaux(t_map *map, int y, int x)
{
	char	tile_value;

	tile_value = map->tiles[y][x];
	if (tile_value == 'C')
		map->c_count++;
	else if (tile_value == 'E')
		map->e_count++;
	else if (tile_value == 'P')
	{
		map->p_count++;
		map->p_y = y;
		map->p_x = x;
	}
	else if (tile_value != '1' && tile_value != '0')
		return (0);
	return (1);
}
