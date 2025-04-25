/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:28:34 by mettalbi          #+#    #+#             */
/*   Updated: 2025/04/25 10:30:05 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	filling_textures(t_game *game)
{
	game->player->bits_per_pixel = game->bits_per_pixel;
	game->textures[0] = game->texture;
	game->textures[1] = game->texture2;
	game->textures[2] = game->texture3;
	game->textures[3] = game->texture4;
	game->player->textures = game->textures;
}
