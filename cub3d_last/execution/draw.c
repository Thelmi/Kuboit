/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krazikho <krazikho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:15:24 by krazikho          #+#    #+#             */
/*   Updated: 2025/01/09 16:20:55 by krazikho         ###   ########.fr       */
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
