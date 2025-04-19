/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_part2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:02:54 by mettalbi          #+#    #+#             */
/*   Updated: 2025/04/19 14:04:28 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel_to_buffer(char *buffer, int x, int y, int color,
			int size_line, int bits_per_pixel)
{
	int	pixel;

	if (x < 0 || x >= 64 * 15 || y < 0 || y >= 64 * 10)
		return ;
	pixel = (y * size_line) + (x * (bits_per_pixel / 8));
	*(unsigned int *)(buffer + pixel) = color;
}

void	texture_init(t_texture *texture, t_texture *texture2)
{
	texture->data = NULL;
	texture->img = NULL;
	texture->size_line = 0;
	texture->bpp = 0;
	texture->endian = 0;
	texture2->data = NULL;
	texture2->img = NULL;
	texture2->size_line = 0;
	texture2->bpp = 0;
	texture2->endian = 0;
}

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	setting_imgs_and_data(t_texture *texture, void *mlx, char *string)
{
	texture->img = mlx_xpm_file_to_image(mlx, string, &texture->width,
			&texture->height);
	texture->data = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->size_line, &texture->endian);
}

void	init_vars_mlx(void *win, void *mlx, t_player *player)
{
	mlx_hook(win, 2, 0, &update_player, player);
	mlx_hook(win, 3, 0, &update_player2, player);
	mlx_loop_hook(mlx, &update_map, player);
	mlx_clear_window(player->mlx, player->win);
	mlx_loop(mlx);
}
