/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amura <amura@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 21:30:51 by antoinemura       #+#    #+#             */
/*   Updated: 2024/04/13 15:47:31 by amura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_end_game_condition(t_map *m, int new_x, int new_y)
{
	if (m->tiles[new_y][new_x] == 'E' && m->c_count == 0)
		ft_printf("Fin du jeu !\n");
}

void	update_tiles_and_images(t_map *m, int new_x, int new_y)
{
	m->tiles_img[new_y][new_x] = m->tiles_img[m->p_y][m->p_x];
	check_end_game_condition(m, new_x, new_y);
	m->tiles[m->p_y][m->p_x] = '0';
	m->tiles[new_y][new_x] = 'P';
}

void	collect_collectible_move(t_map *m, int new_x, int new_y)
{
	if (m->tiles[new_y][new_x] == 'C')
	{
		m->c_count--;
		mlx_delete_image(m->mlx, m->tiles_img[new_y][new_x]);
		ft_printf("Trouvé ! Plus que %d\n", m->c_count);
	}
}

void	handle_move(t_map *m, int dx, int dy)
{
	int			new_x;
	int			new_y;
	static int	move_c = 0;

	new_x = m->p_x + dx;
	new_y = m->p_y + dy;
	if (is_valid_move(m, new_y, new_x))
	{
		if (dx != 0)
			m->tiles_img[m->p_y][m->p_x]->instances[0].x += 32 * dx;
		if (dy != 0)
			m->tiles_img[m->p_y][m->p_x]->instances[0].y += 32 * dy;
		collect_collectible_move(m, new_x, new_y);
		update_tiles_and_images(m, new_x, new_y);
		m->p_x = new_x;
		m->p_y = new_y;
		ft_printf("%d\n", ++move_c);
	}
}

void	key_hook(mlx_key_data_t keydata, void *map)
{
	t_map	*m;
	int		dx;
	int		dy;

	dx = 0;
	dy = 0;
	m = (t_map *)map;
	if (keydata.action == MLX_RELEASE || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_A)
			dx = -1;
		else if (keydata.key == MLX_KEY_D)
			dx = 1;
		else if (keydata.key == MLX_KEY_W)
			dy = -1;
		else if (keydata.key == MLX_KEY_S)
			dy = 1;
		else if (keydata.key == MLX_KEY_ESCAPE)
			close_program(map);
		if (dx != 0 || dy != 0)
			handle_move(m, dx, dy);
	}
}
