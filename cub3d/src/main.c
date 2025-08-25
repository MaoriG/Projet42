/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 16:13:54 by mgobert           #+#    #+#             */
/*   Updated: 2025/08/25 20:35:18 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == W)
		game->player.key_up = true;
	if (keycode == S)
		game->player.key_down = true;
	if (keycode == A)
		game->player.key_left = true;
	if (keycode == D)
		game->player.key_right = true;
	if (keycode == LEFT)
		game->player.left_rotate = true;
	if (keycode == RIGHT)
		game->player.right_rotate = true;
	if (keycode == ESC)
	{
		destroy_game(game);
		exit(0);
	}
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == W)
		game->player.key_up = false;
	if (keycode == S)
		game->player.key_down = false;
	if (keycode == A)
		game->player.key_left = false;
	if (keycode == D)
		game->player.key_right = false;
	if (keycode == LEFT)
		game->player.left_rotate = false;
	if (keycode == RIGHT)
		game->player.right_rotate = false;
	return (0);
}

void	clear_image(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, 0, game);
			x++;
		}
		y++;
	}
}

void	init_game(t_game *game)
{
	if (get_map(game, "map.cub") != 0)
		ft_error("Erreur : chargement de la map\n", game);
	init_player(&game->player, game);
	if (!(game->mlx = mlx_init()))
		ft_error("Erreur init mlx\n", game);
	if (!(game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "game")))
		ft_error("Erreur creation fenetre\n", game);
	if (!(game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT)))
		ft_error("Erreur creation image\n", game);
	if (!(game->data = mlx_get_data_addr(game->img, &game->bpp,
				&game->size_line, &game->endian)))
		ft_error("Erreur accès data image\n", game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	load_texture(game, &game->textures[0], "textures/north.xpm");
	load_texture(game, &game->textures[1], "textures/south.xpm");
	load_texture(game, &game->textures[2], "textures/east.xpm");
	load_texture(game, &game->textures[3], "textures/west.xpm");
}

float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

int	main(void)
{
	t_game	game;

	init_game(&game);
	game.running = true;
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_hook(game.win, 17, 0, exit_game, &game);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	destroy_game(&game);
	return (0);
}
