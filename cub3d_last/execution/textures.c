/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelmy <thelmy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 18:53:17 by krazikho          #+#    #+#             */
/*   Updated: 2025/01/13 18:55:23 by thelmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	put_pixel_to_image(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	pixel = img->adrs + (y * img->linelen + x * (img->bitsperpixel / 8));
	*(int *)pixel = color;
}

static void	get_pixels(t_game *game, int x_screen, t_img *texture)
{
	double	texture_step;
	char	*pixel;
	int		color;

	if (game->ray.hit_orientation == 0 || game->ray.hit_orientation == 1)
		game->wall.tex_x = (double)game->pl_x_tile + game->ray.ray_length
			* game->ray.cos;
	else
		game->wall.tex_x = (double)game->pl_y_tile - game->ray.ray_length
			* game->ray.sin;
	
	game->wall.tex_x = (fmod(game->wall.tex_x, 30.0)) / 30.0 * 128.0;

	texture_step = (double)TEXTURE_HEIGHT / game->wall.wallslice_height;

	game->wall.tex_y = (game->wall.start_y - (HEIGHT - game->wall.wallslice_height) / 2) * texture_step;

	while (game->wall.start_y < game->wall.end_y)
	{
		if ((int)game->wall.tex_y >= 128)
			game->wall.tex_y = 127.0;
		pixel = texture->adrs + ((int)game->wall.tex_y * texture->linelen
				+ (int)game->wall.tex_x * (texture->bitsperpixel / 8));
		color = *(int *)pixel;
		put_pixel_to_image(&game->img, x_screen, game->wall.start_y, color);
		game->wall.tex_y += texture_step;
		game->wall.start_y++;
	}
}

void	draw_wall_slice(t_game *game, int x_screen)
{
	t_img	*texture;

	game->wall.start_y = HEIGHT / 2 - game->wall.wallslice_height / 2;
	game->wall.end_y = game->wall.start_y + game->wall.wallslice_height;
	if (game->wall.start_y < 0)
		game->wall.start_y = 0;
	if (game->wall.end_y >= HEIGHT)
		game->wall.end_y = HEIGHT - 1;
	if (game->ray.hit_orientation == 0)
		texture = &game->south_texture;
	else if (game->ray.hit_orientation == 1)
		texture = &game->north_texture;
	else if (game->ray.hit_orientation == 2)
		texture = &game->west_texture;
	else
		texture = &game->east_texture;
	get_pixels(game, x_screen, texture);
}

void	get_we_textures(t_game *game)
{
	int	width;
	int	height;

	width = TEXTURE_WIDTH;
	height = TEXTURE_HEIGHT;
	game->east_texture.img = mlx_xpm_file_to_image(game->mlx_connection,
			game->ea, &width, &height);
	if (!game->east_texture.img)
	{
		write(2, "Error! Failed to load east texture.\n", 36);
		free_game_failure(game);
	}
	game->east_texture.adrs = mlx_get_data_addr(game->east_texture.img,
			&game->east_texture.bitsperpixel, &game->east_texture.linelen,
			&game->east_texture.endian);
	game->west_texture.img = mlx_xpm_file_to_image(game->mlx_connection,
			game->we, &width, &height);
	if (!game->west_texture.img)
	{
		write(2, "Error! Failed to load west texture.\n", 36);
		free_game_failure(game);
	}
	game->west_texture.adrs = mlx_get_data_addr(game->west_texture.img,
			&game->west_texture.bitsperpixel, &game->west_texture.linelen,
			&game->west_texture.endian);
}

void	get_ns_textures(t_game *game)
{
	int	width;
	int	height;

	width = TEXTURE_WIDTH;
	height = TEXTURE_HEIGHT;
	game->north_texture.img = mlx_xpm_file_to_image(game->mlx_connection,
			game->no, &width, &height);
	if (!game->north_texture.img)
	{
		write(2, "Error! Failed to load north texture.\n", 37);
		free_game_failure(game);
	}
	game->north_texture.adrs = mlx_get_data_addr(game->north_texture.img,
			&game->north_texture.bitsperpixel, &game->north_texture.linelen,
			&game->north_texture.endian);
	game->south_texture.img = mlx_xpm_file_to_image(game->mlx_connection,
			game->so, &width, &height);
	if (!game->south_texture.img)
	{
		write(2, "Error! Failed to load south texture.\n", 37);
		free_game_failure(game);
	}
	game->south_texture.adrs = mlx_get_data_addr(game->south_texture.img,
			&game->south_texture.bitsperpixel, &game->south_texture.linelen,
			&game->south_texture.endian);
}
