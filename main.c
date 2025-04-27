/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 13:25:48 by mettalbi          #+#    #+#             */
/*   Updated: 2025/04/27 22:35:47 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parsing.h"

void	allocating_for_textures(t_texture **texture, t_texture **texture2,
			t_texture **texture3, t_texture **texture4)
{
	*texture = zyalloc(sizeof(t_texture));
	*texture2 = zyalloc(sizeof(t_texture));
	*texture3 = zyalloc(sizeof(t_texture));
	*texture4 = zyalloc(sizeof(t_texture));
}

void	setting_imgs(t_game *game, void *mlx)
{
	setting_imgs_and_data(game->texture2, mlx, game->strings->so_texture);
	setting_imgs_and_data(game->texture3, mlx, game->strings->ea_texture);
	setting_imgs_and_data(game->texture4, mlx, game->strings->we_texture);
}

void	assigning_values_to_player(t_player *player, char *buffer,
			void *img, int size_line)
{
	player->buffer = buffer;
	player->size_line = size_line;
	player->img = img;
}

void	assigning_some_values(t_texture ***textures,
			t_player **player, void **mlx, void **win)
{
	*textures = zyalloc (sizeof(t_texture) * 4);
	*player = zyalloc(sizeof(t_player));
	*mlx = mlx_init();
	*win = mlx_new_window(*mlx, 64 * 15, 64 * 10, "window");
}

int	main(int ac, char **av)
{
	t_game	*game;

	game = zyalloc(sizeof(t_game));
	assigning_some_values(&game->textures,
		&game->player, &game->mlx, &game->win);
	allocating_for_textures(&game->texture, &game->texture2,
		&game->texture3, &game->texture4);
	game->strings = retrieving(ac, av);
	game->map = game->strings->map;
	game->player->longest_row = get_longest_row(game->strings->map);
	game->player->get_num_rows = get_num_rows(game->strings->map);
	game->map = pad_map(game->map,
			game->player->get_num_rows, game->player->longest_row, '1');
	locate_player(game->player, game->map);
	setting_imgs_and_data(game->texture, game->mlx, game->strings->no_texture);
	setting_imgs(game, game->mlx);
	game->player->texture = game->texture;
	game->img = mlx_new_image(game->mlx, 64 * 15, 64 * 10);
	game->buffer = mlx_get_data_addr(game->img, &game->bits_per_pixel,
			&game->size_line, &game->endian);
	player_init(game->player, game->map, game->mlx, game->win);
	assigning_values_to_player(game->player, game->buffer,
		game->img, game->size_line);
	filling_textures(game);
	init_vars_mlx(game->win, game->mlx, game->player, game);
}
