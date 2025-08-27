/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 18:58:35 by mgobert           #+#    #+#             */
/*   Updated: 2025/08/27 18:44:58 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	load_texture(void *mlx, t_tex *tex, char *path)
{
	if (!path)
	{
		printf("Error\nMissing texture path\n");
		return (1);
	}
	tex->img = mlx_xpm_file_to_image(mlx, path, &tex->width, &tex->height);
	if (!tex->img)
	{
		printf("Error\nFailed to load texture: %s\n", path);
		return (1);
	}
	tex->data = mlx_get_data_addr(tex->img, &tex->bpp, &tex->size_line,
			&tex->endian);
	return (0);
}

static void	draw_floor(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = HEIGHT / 2;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, game->config.floor_color, game);
			x++;
		}
		y++;
	}
}

void	draw_ceiling(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, game->config.ceil_color, game);
			x++;
		}
		y++;
	}
	draw_floor(game);
}

int	get_tex_pixel(t_tex *tex, int x, int y)
{
	int		index;
	char	*pixel;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0x000000);
	index = (y * tex->size_line) + (x * (tex->bpp / 8));
	pixel = &tex->data[index];
	return (*(int *)pixel);
}

int	init_textures(t_game *game)
{
	if (load_texture(game->mlx, &game->textures[0], game->config.no_path))
		return (1);
	if (load_texture(game->mlx, &game->textures[1], game->config.so_path))
		return (1);
	if (load_texture(game->mlx, &game->textures[2], game->config.ea_path))
		return (1);
	if (load_texture(game->mlx, &game->textures[3], game->config.we_path))
		return (1);
	return (0);
}
