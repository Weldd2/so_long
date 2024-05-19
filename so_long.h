/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amura <amura@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 00:24:07 by antoinemura       #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/04/13 15:49:09 by amura            ###   ########.fr       */
=======
/*   Updated: 2024/05/19 22:47:26 by antoinemura      ###   ########.fr       */
>>>>>>> b07945d (changes)
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "MLX42/include/MLX42/MLX42.h"
# include "./libft/libft.h"
# include <fcntl.h>

typedef struct s_map
{
	char		**tiles;
	mlx_image_t	***tiles_img;
	mlx_t		*mlx;
	int			x_l;
	int			y_l;
	int			p_y;
	int			p_x;
	int			c_count;
	int			e_count;
	int			p_count;
}	t_map;

int		open_map(char	*file_path);
char	**read_map(char *file_path, int y_l);
int		est_rectangulaire(char	*file_path, int *y_l, int *x_l);
int		est_map_fermee(t_map *map);
t_map	*init_map(char **tiles, int y_l, int x_l, int graph);
void	free_tiles_img(t_map *map);
void	fill_map(t_map *map, mlx_t *mlx);
void	put_image(int x, int y, t_map *map, mlx_t *mlx);
void	close_program(t_map *map);
void	free_map(t_map *map);
int		iterate_map(t_map *map, int func(t_map *, int, int));
int		compteur_speciaux(t_map *map, int y, int x);
int		est_resoluble(t_map *map);
int		resoudre(t_map *m);
int		is_valid_move(t_map *m, int newY, int newX);
void	print_map(t_map *m);
void	handle_move(t_map *m, int dx, int dy);
void	key_hook(mlx_key_data_t keydata, void *map);
int		resoudre(t_map *m);
int		est_resoluble(t_map *map);
int		reset_map_tile_value(t_map *m, int y, int x);

#endif