/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 19:03:56 by mgobert           #+#    #+#             */
/*   Updated: 2025/09/03 16:04:20 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	clean_map(t_game *game, char **map)
{
	int	i;

	i = 0;
	while (i < game->map_height)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->textures[i].img)
			mlx_destroy_image(game->mlx, game->textures[i].img);
		i++;
	}
}

int	exit_game(t_game *game)
{
	game->running = false;
	destroy_game(game);
	exit(0);
	return (0);
}

void	destroy_game(t_game *game)
{
	if (!game)
		return ;
	if (game->map)
		clean_map(game, game->map);
	free_textures(game);
	if (game->img && game->mlx)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win && game->mlx)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	if (game->config.no_path)
		free(game->config.no_path);
	if (game->config.so_path)
		free(game->config.so_path);
	if (game->config.we_path)
		free(game->config.we_path);
	if (game->config.ea_path)
		free(game->config.ea_path);
	drain_gnl_fd(game->fd);
}

void	clear_image(t_game *game)
{
	ft_bzero(game->data, HEIGHT * game->size_line);
}
