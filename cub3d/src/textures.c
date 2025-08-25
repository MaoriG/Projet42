/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 18:58:35 by mgobert           #+#    #+#             */
/*   Updated: 2025/08/25 20:04:02 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	load_texture(t_game *game, t_tex *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(game->mlx, path, &tex->width,
			&tex->height);
	if (!tex->img)
		ft_error("Erreur chargement texture", game);
	tex->data = mlx_get_data_addr(tex->img, &tex->bpp, &tex->size_line,
			&tex->endian);
	if (!tex->data)
		ft_error("Erreur accès texture data", game);
}

void	draw_floor_ceiling(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, CEILING_COLOR, game);
			x++;
		}
		y++;
	}
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, FLOOR_COLOR, game);
			x++;
		}
		y++;
	}
}

int	get_tex_pixel(t_tex *tex, int x, int y)
{
	int index;
	char *pixel;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0x000000);
	index = (y * tex->size_line) + (x * (tex->bpp / 8));
	pixel = &tex->data[index];
	return (*(int *)pixel);
}