/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:52:45 by mettalbi          #+#    #+#             */
/*   Updated: 2025/04/29 16:34:28 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <limits.h>
# include "parsing.h"

# define SCREEN_HEIGHT 640
# define SCREEN_WIDTH 960
# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64

typedef struct s_garbage
{
	void				*address;
	struct s_garbage	*next;
}	t_garbage;

typedef struct s_wall_check
{
	int		check_x;
	int		check_y;
	double	corner_x[2];
	double	corner_y[2];
	int		i;
	int		j;	
}	t_wall_check;

typedef struct s_ray
{
	double	ray_angle;
	double	wallhitx;
	double	wallhity;
	double	vertwallhitx;
	double	vertwallhity;
	int		downward_ray;
	int		upward_ray;
	int		left_ray;
	int		right_ray;
	double	distance;
	int		hit_vertical;
	double	x_interecept;
	double	y_interecept;
	double	xstep;
	double	y_step;
	double	next_touch_y;
	double	next_touch_x;
	int		wall_found;
	int		vert_wall_found;
	bool	north_face;
	bool	south_face;
	bool	east_face;
	bool	west_face;
}	t_ray;

typedef struct s_texture
{
	void	*img;
	char	*data;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}	t_texture;

typedef struct s_player
{
	void		*buffer;
	int			size_line;
	int			bits_per_pixel;
	void		*img;
	double		x;
	double		y;
	int			turn_direction;
	int			walkdirection;
	double		rotationangle;
	int			movespeed;
	int			radius;
	double		rotationspeed;
	int			get_num_rows;
	int			longest_row;
	char		**staticarray;
	void		*mlx;
	void		*win;
	int			c_color;
	int			f_color;
	t_ray		*rays;
	t_texture	*texture;
	t_texture	**textures;
}	t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_player	*player;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	char		**map;
	t_texture	**textures;
	t_texture	*texture;
	t_texture	*texture2;
	t_texture	*texture3;
	t_texture	*texture4;
	t_strings	*strings;
	char		*buffer;
	void		*img;
}	t_game;

typedef struct s_wallclump
{
	int			wallheight;
	uint32_t	*wall_texture;
	int			wall_top;
	int			wall_bottom;
	int			i;
}	t_wall_clumper;

typedef struct s_pixel_draw
{
	int	x;
	int	y;
	int	size_line;
}	t_pixel_draw;

int			exit_window(t_player *player);
void		draw_player(t_player *player, void *win, void *mlx);
int			update_player2(int keycode, t_player *player);
int			update_player(int keycode, t_player *player);
int			update_map(t_player *player);
t_ray		*cast_rays(t_player *player);
void		render(t_player *player, t_ray *ray, int j);
void		draw_player(t_player *player, void *win, void *mlx);
void		player_init(t_player *player, char **staticArray,
				void *mlx, void *win);
int			its_a_wall(double x, double y, t_player *player);
void		draw_line(t_player *player, void *mlx, void *win);
t_strings	*retrieving(int ac, char **av);
void		put_pixel_to_buffer(int x, int y, int color, t_player *player);
void		texture_init(t_texture *texture, t_texture *texture2);
char		*ft_strcpy(char *dest, const char *src);
void		setting_imgs_and_data(t_texture *texture, void *mlx, char *string);
void		init_vars_mlx(void *win, void *mlx, t_player *player, t_game *game);
int			get_num_rows(char **array);
int			get_longest_row(char **map);
char		**pad_map(char **map, int num_rows, int longest_row, char pad_char);
void		setting_angle(char **map, t_player *player, int i, int j);
void		locate_player(t_player *player, char **map);
double		distance_between(double player_x, double player_y,
				double wall_hitx, double wall_hity);
void		check_horizontal_inter2(t_ray *rays, int i, t_player *player);
void		check_horizontal_inter3(t_ray *rays, t_player *player, int i);
void		check_horizontal_inter(t_player *player, t_ray *rays, int i);
int			its_a_wall2(double x, double y, t_player *player);
uint32_t	*wall_draw_3d_2(t_ray *ray, int i, t_player *player);
void		draw(t_ray *ray, int i, t_player *player, int wallheight);
void		check_vertical_inter2(t_ray *rays, int i);
void		ray_casting2(t_ray *rays, int i);
void		ray_casting3(double horizontal_hit, double vertical_hit,
				t_ray *rays, int i);
void		check_vertical_inter(t_player *player, t_ray *rays, int i);
void		filling_textures(t_game *game);
void		*zyalloc(long long size);
int			its_a_wall3(double x, double y, t_player *player);

#endif