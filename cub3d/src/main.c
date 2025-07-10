/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 16:13:54 by mgobert           #+#    #+#             */
/*   Updated: 2025/07/10 18:38:41 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void put_pixel(int x, int y, int color, t_game *game)
{
    int index;
    
    if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
        return;
    index = y * game->size_line + x * game->bpp / 8;
    game->data[index] = color & 0xFF;
    game->data[index + 1] = (color >> 8) & 0xFF;
    game->data[index + 2] = (color >> 16) & 0xFF;
}
void draw_square(int x, int y, int size, int color, t_game *game)
{
    int i;

    i = 0;
    while (i < size)
    {
        put_pixel(x + i, y, color, game);
        put_pixel(x, y + i, color, game);
        put_pixel(x + size, y + i, color, game);
        put_pixel(x + i, y + size, color, game);
        i++;  
    }
}

void clear_image(t_game *game)
{
    int y;
    int x;

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

void init_game(t_game *game)
{
    if (get_map(game, "map.cub") != 0)
        ft_error("Erreur : chargement de la map\n");
    init_player(&game->player, game);
    if (!(game->mlx = mlx_init()))
        ft_error("Erreur init mlx\n");
    if (!(game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "game")))
        ft_error("Erreur creation fenetre\n");
    if (!(game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT)))
        ft_error("Erreur creation image\n");
    if (!(game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, 
    &game->endian)))
        ft_error("Erreur accès data image\n");
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

float distance (float x, float y)
{
    return (sqrt(x * x + y * y));
}

int	main(void)
{
    t_game game;

    init_game(&game);
    
    mlx_hook(game.win, 2, 1L<<0, key_press, &game.player);
    mlx_hook(game.win, 3, 1L<<1, key_release, &game.player);
    
    mlx_loop_hook(game.mlx, draw_loop, &game);
    
    mlx_loop(game.mlx);
    return (0);
}