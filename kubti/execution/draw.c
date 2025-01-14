/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelmy <thelmy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:15:24 by krazikho          #+#    #+#             */
/*   Updated: 2025/01/14 19:55:06 by thelmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	draw_floornceiling(t_game *game)
{
	unsigned int	*dst;
	int				i;
	int				half_pixels;
	int				total_pixels;

	dst = (unsigned int *)game->img.adrs;
	total_pixels = WIDTH * HEIGHT;
	half_pixels = total_pixels / 2;
	i = 0;
	while (i < half_pixels)
	{
		dst[i] = game->ceil_hex;
		i++;
	}
	while (i < total_pixels)
	{
		dst[i] = game->floor_hex;
		i++;
	}
}

void	draw_walls(t_game *game)
{
	int		x_screen;
	double	first_ray;
	double	delta_angle;

	x_screen = 0;
	first_ray = (game->pl_view_ang + FOV_ANGLE / 2);
	delta_angle = FOV_ANGLE / WIDTH;
	while (x_screen < WIDTH)
	{
		game->ray.ray_angle = first_ray - x_screen * delta_angle;
		if (game->ray.ray_angle < 0)
			game->ray.ray_angle += 2 * M_PI;
		if (game->ray.ray_angle >= 2 * M_PI)
			game->ray.ray_angle -= 2 * M_PI;
		game->ray.cos = cos(game->ray.ray_angle);
		game->ray.sin = sin(game->ray.ray_angle);
		game->ray.ray_length = cast_ray(game);
		game->ray.ray_length_corrected = game->ray.ray_length
			* cos(game->ray.ray_angle - game->pl_view_ang);
		game->wall.wallslice_height = HEIGHT * (1
				/ (game->ray.ray_length_corrected / TILE_SIZE));
		draw_wall_slice(game, x_screen);
		x_screen++;
	}
}

void	draw(t_game *game)
{
	mlx_clear_window(game->mlx_connection, game->mlx_window);
	draw_floornceiling(game);
	init_ray_values(game);
	init_walls(game);
	draw_walls(game);
	mlx_put_image_to_window(game->mlx_connection, game->mlx_window,
		game->img.img, 0, 0);
}
