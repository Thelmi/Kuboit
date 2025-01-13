/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelmy <thelmy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 19:49:16 by thelmy            #+#    #+#             */
/*   Updated: 2025/01/13 18:54:48 by thelmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	free_game_failure(t_game *game)
{
	free_textures(*game);
	free_map(*game);
	if (game->east_texture.img)
		mlx_destroy_image(game->mlx_connection, game->east_texture.img);
	if (game->west_texture.img)
		mlx_destroy_image(game->mlx_connection, game->west_texture.img);
	if (game->north_texture.img)
		mlx_destroy_image(game->mlx_connection, game->north_texture.img);
	if (game->south_texture.img)
		mlx_destroy_image(game->mlx_connection, game->south_texture.img);
	if (game->img.img)
		mlx_destroy_image(game->mlx_connection, game->img.img);
	mlx_destroy_window(game->mlx_connection, game->mlx_window);
	exit(EXIT_FAILURE);
	return (1);
}

int	free_game_success(t_game *game)
{
	free_textures(*game);
	free_map(*game);
	if (game->east_texture.img)
		mlx_destroy_image(game->mlx_connection, game->east_texture.img);
	if (game->west_texture.img)
		mlx_destroy_image(game->mlx_connection, game->west_texture.img);
	if (game->north_texture.img)
		mlx_destroy_image(game->mlx_connection, game->north_texture.img);
	if (game->south_texture.img)
		mlx_destroy_image(game->mlx_connection, game->south_texture.img);
	if (game->img.img)
		mlx_destroy_image(game->mlx_connection, game->img.img);
	mlx_destroy_window(game->mlx_connection, game->mlx_window);
	exit(EXIT_SUCCESS);
	return (0);
}

void	game_init(t_game *game)
{
	game->map = NULL;
	game->copy = NULL;
	game->no = NULL;
	game->so = NULL;
	game->we = NULL;
	game->ea = NULL;
	game->flr_r = -1;
	game->flr_g = -1;
	game->flr_b = -1;
	game->cl_r = -1;
	game->cl_g = -1;
	game->cl_b = -1;
	game->floor_hex = 0;
	game->ceil_hex = 0;
	game->pl_view = 0;
	game->pl_x = -1;
	game->pl_y = -1;
	game->free_flag = 0;
	game->newline = 0;
	game->north_texture.img = 0;
	game->south_texture.img = 0;
	game->west_texture.img = 0;
	game->east_texture.img = 0;
	game->img.img = NULL;
}

int	main(int ac, char **av)
{
	t_game	game;

	game_init(&game);
	game = parsing(game, ac, av);
	game.mlx_connection = mlx_init();
	game.mlx_window = mlx_new_window(game.mlx_connection, WIDTH,
			HEIGHT, "Kub3T");
	init_player_view_and_position(&game);
	game.img.img = mlx_new_image(game.mlx_connection, WIDTH, HEIGHT);
	game.img.adrs = mlx_get_data_addr(game.img.img, &game.img.bitsperpixel,
			&game.img.linelen, &game.img.endian);
	get_we_textures(&game);
	get_ns_textures(&game);
	draw(&game);
	mlx_key_hook(game.mlx_window, key_hook, &game);
	mlx_hook(game.mlx_window, 17, 0, free_game_success, &game);
	mlx_loop(game.mlx_connection);
	return (0);
}
