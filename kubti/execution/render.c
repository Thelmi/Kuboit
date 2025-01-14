/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelmy <thelmy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:33:31 by krazikho          #+#    #+#             */
/*   Updated: 2025/01/14 20:01:57 by thelmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	corner(t_game *game, int *grid_x, int *grid_y)
{
	*grid_y += game->wall.step_y;
	*grid_x += game->wall.step_x;
	if (*grid_x != (int)t_strlen(game->map[*grid_y])
		&& game->map[*grid_y][*grid_x] != '1'
		&& game->map[*grid_y][*grid_x] != ' ')
	{
		game->ray.first_hor_int_c += game->ray.c_per_unit_y;
		game->ray.first_ver_int_c += game->ray.c_per_unit_x;
	}
}

static void	compare_intersections(t_game *game, int grid_x, int grid_y)
{
	while (grid_x != (int)t_strlen(game->map[grid_y])
		&& game->map[grid_y][grid_x] != '1' && game->map[grid_y][grid_x] != ' ')
	{
		if ((game->ray.first_hor_int_c) == (game->ray.first_ver_int_c))
			corner(game, &grid_x, &grid_y);
		else if ((game->ray.first_hor_int_c) < (game->ray.first_ver_int_c))
		{
			grid_y += game->wall.step_y;
			if (grid_x != (int)t_strlen(game->map[grid_y])
				&& game->map[grid_y][grid_x] != '1'
				&& game->map[grid_y][grid_x] != ' ')
				game->ray.first_hor_int_c += game->ray.c_per_unit_y;
		}
		else if ((game->ray.first_hor_int_c) > (game->ray.first_ver_int_c))
		{
			grid_x += game->wall.step_x;
			if (grid_x != (int)t_strlen(game->map[grid_y])
				&& game->map[grid_y][grid_x] != '1'
				&& game->map[grid_y][grid_x] != ' ')
				game->ray.first_ver_int_c += game->ray.c_per_unit_x;
		}
	}
}

static void	protect(t_game *game)
{
	if (fabs(game->ray.sin) > 0.000001)
		game->ray.first_hor_int_c = game->wall.a / fabs(game->ray.sin);
	else
		game->ray.first_hor_int_c = INFINITY;
	if (fabs(game->ray.cos) > 0.000001)
		game->ray.first_ver_int_c = game->wall.b / fabs(game->ray.cos);
	else
		game->ray.first_ver_int_c = INFINITY;
	if (fabs(sin(game->ray.ray_angle)) > 0.000001)
		game->ray.c_per_unit_y = TILE_SIZE / fabs(sin(game->ray.ray_angle));
	else
		game->ray.c_per_unit_y = INFINITY;
	if (fabs(cos(game->ray.ray_angle)) > 0.000001)
		game->ray.c_per_unit_x = TILE_SIZE / fabs(cos(game->ray.ray_angle));
	else
		game->ray.c_per_unit_x = INFINITY;
}

static double	get_ray_length(t_game *game)
{
	int	grid_x;
	int	grid_y;

	grid_x = game->pl_x;
	grid_y = game->pl_y;
	protect(game);
	compare_intersections(game, grid_x, grid_y);
	if (game->ray.first_hor_int_c < game->ray.first_ver_int_c)
	{
		if (game->ray.sin > 0)
			game->ray.hit_orientation = 0;
		else
			game->ray.hit_orientation = 1;
		return (game->ray.first_hor_int_c);
	}
	else
	{
		if (game->ray.cos > 0)
			game->ray.hit_orientation = 2;
		else
			game->ray.hit_orientation = 3;
		return (game->ray.first_ver_int_c);
	}
}

double	cast_ray(t_game *game)
{
	if (game->ray.sin > 0)
	{
		game->wall.a = game->pl_y_tile - game->pl_y * TILE_SIZE;
		game->wall.step_y = -1;
	}
	else if (game->ray.sin < 0)
	{
		game->wall.a = (game->pl_y + 1) * TILE_SIZE - game->pl_y_tile;
		game->wall.step_y = 1;
	}
	if (game->ray.cos < 0.0)
	{
		game->wall.b = game->pl_x_tile - game->pl_x * TILE_SIZE;
		game->wall.step_x = -1;
	}
	else if (game->ray.cos > 0.0)
	{
		game->wall.b = (game->pl_x + 1) * TILE_SIZE - game->pl_x_tile;
		game->wall.step_x = 1;
	}
	if (game->wall.a == 0)
		game->wall.a += 1;
	if (game->wall.b == 0)
		game->wall.b += 1;
	return (get_ray_length(game));
}
