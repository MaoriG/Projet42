/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 16:13:54 by mgobert           #+#    #+#             */
/*   Updated: 2025/08/28 20:55:40 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	init_game_help(t_game *game)
{
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line,
			&game->endian);
	if (!(game->img))
	{
		printf("Error\nCreating a new image\n");
		return (1);
	}
	if (!(game->data))
	{
		printf("Error\nImage data acces\n");
		return (1);
	}
	if (init_textures(game))
		return (1);
	return (0);
}

int	init_game(t_game *game, char *map)
{
	if (parse_cub_file(game, map) != 0)
	{
		destroy_game(game);
		printf("Error\nLoading map\n");
		return (2);
	}
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "game");
	if (init_player(&game->player, game))
		return (1);
	if (!(game->mlx))
	{
		printf("Error\nInitializing mlx\n");
		return (1);
	}
	if (!(game->win))
	{
		printf("Error\nWith window creation\n");
		return (1);
	}
	if (init_game_help(game))
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	game;
	int		ret;

	if (ac != 2)
		return (printf("Error\nUsage: ./cub3d map.cub\n"));
	ft_bzero(&game, sizeof(t_game));
	ret = init_game(&game, av[1]);
	if (ret == 2)
		return (1);
	if (ret == 1)
		return (destroy_game(&game), 1);
	game.running = true;
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_hook(game.win, 17, 0, exit_game, &game);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	destroy_game(&game);
	return (0);
}
