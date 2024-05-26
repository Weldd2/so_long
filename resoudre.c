/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resoudre.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amura <amura@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 21:44:37 by antoinemura       #+#    #+#             */
/*   Updated: 2024/05/26 10:31:47 by amura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_victory_condition(t_map *m)
{
	char	tile;

	tile = m->tiles[m->p_y][m->p_x];
	return (tile == 'E' && m->c_count == 0);
}

int	check_stop_condition(t_map *m)
{
	char	tile;

	tile = m->tiles[m->p_y][m->p_x];
	return (tile == '1' || tile == '2' || tile == 'E');
}

void	collect_collectible(t_map *m)
{
	if (m->tiles[m->p_y][m->p_x] == 'C')
	{
		m->c_count--;
		iterate_map(m, reset_map_tile_value);
		m->tiles[m->p_y][m->p_x] = 'P';
	}
}

int	explore_recursive(t_map *m, int direction_index)
{
	int					new_y;
	int					new_x;
	static const int	g_directions[4][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};

	new_y = m->p_y + g_directions[direction_index][0];
	new_x = m->p_x + g_directions[direction_index][1];
	if (is_valid_move(m, new_y, new_x))
	{
		m->p_y = new_y;
		m->p_x = new_x;
		if (resoudre(m))
			return (1);
		m->p_y -= g_directions[direction_index][0];
		m->p_x -= g_directions[direction_index][1];
	}
	return (0);
}

int	resoudre(t_map *m)
{
	int	i;

	i = 0;
	if (check_victory_condition(m))
		return (1);
	if (check_stop_condition(m))
		return (0);
	collect_collectible(m);
	m->tiles[m->p_y][m->p_x] = '2';
	while (i < 4)
	{
		if (explore_recursive(m, i))
			return (1);
		i++;
	}
	return (0);
}
