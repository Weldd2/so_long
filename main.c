/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amura <amura@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 17:07:31 by antoinemura       #+#    #+#             */
/*   Updated: 2024/05/26 11:04:09 by amura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*get_texture_path(char tile)
{
	if (tile == 'C')
		return ("./assets/fleur.png");
	if (tile == '1')
		return ("./assets/brique.png");
	if (tile == '0')
		return ("./assets/planche.png");
	if (tile == 'P')
		return (NULL);
	if (tile == 'E')
		return ("./assets/echelle.png");
	return (NULL);
}

void	put_image(int x, int y, t_map *map, mlx_t *mlx)
{
	char			tile_value;
	mlx_texture_t	*texture;
	mlx_image_t		*img;
	char			*texture_path;

	tile_value = map->tiles[y][x];
	if (tile_value == 'E' || tile_value == 'C' || tile_value == 'P')
	{
		texture = mlx_load_png(get_texture_path('0'));
		img = mlx_texture_to_image(mlx, texture);
		map->tiles_img[y][x] = img;
		mlx_image_to_window(mlx, img, x * 32, y * 32);
		mlx_delete_texture(texture);
	}
	texture_path = get_texture_path(tile_value);
	if (texture_path)
	{
		texture = mlx_load_png(texture_path);
		img = mlx_texture_to_image(mlx, texture);
		map->tiles_img[y][x] = img;
		mlx_image_to_window(mlx, img, x * 32, y * 32);
		mlx_delete_texture(texture);
	}
}

void	close_program(t_map *map)
{
	mlx_close_window(map->mlx);
}

static void	error(char *message, t_map *map)
{
	if (map != NULL)
	{
		free_map(map);
	}
	ft_printf("Erreur\n%s\n", message);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	mlx_t	*mlx;
	t_map	*map;
	char	**tiles;
	int		x_l;
	int		y_l;

	if (argc < 2)
		error("Le nombre d'argument n'est pas valide.\n", NULL);
	if (!est_rectangulaire(argv[1], &y_l, &x_l))
		error("La carte indiquée n'est pas rectangulaire ou existe pas.", NULL);
	tiles = read_map(argv[1], y_l);
	map = init_map(tiles, y_l, x_l);
	if (!est_map_fermee(map) || !iterate_map(map, compteur_speciaux))
		error("La carte n'est pas valide.", map);
	if ((map->c_count < 1 || map->e_count != 1 || map->p_count != 1)
		|| !est_resoluble(map))
		error("pas résoluble ou n'a pas assez de collectible.", map);
	mlx = mlx_init(32 * map->x_l, 32 * map->y_l, "Minecraft", true);
	fill_map(map, mlx);
	map->mlx = mlx;
	mlx_key_hook(mlx, &key_hook, map);
	mlx_loop(mlx);
	free_map(map);
}
