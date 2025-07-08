/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 16:13:54 by mgobert           #+#    #+#             */
/*   Updated: 2025/07/08 19:23:20 by mgobert          ###   ########.fr       */
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
void draw_map(t_game *game)
{
    char **map;
    int color;
    int y;
    int x;
    
    color = 0x0000FF;
    map = game->map;
    y = 0;
    while (map[y])
    {
        x = 0;
        while (map[y][x])
        {
            if (map[y][x] == '1')
                draw_square(x * BLOCK, y * BLOCK, BLOCK, color, game);
            x++;
        }
        y++;
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

bool touch(float px, float py, t_game *game)
{
    int x;
    int y;
    
    x = px / BLOCK;
    y = py / BLOCK;
    if (y < 0 || y >= game->map_height || x < 0 || x >= ft_strlen(game->map[y]))
        return true;
    if (game->map[y][x] == '1')
        return true;
    return false;
}
float distance (float x, float y)
{
    return (sqrt(x * x + y * y));
}

float fixed_dist(float x1, float y1, float x2, float y2, t_game *game)
{
    float delta_x;
    float delta_y;
    float angle;
    float fix_dist;

    delta_x = x2 - x1;
    delta_y = y2 - y1;
    angle = atan2(delta_y, delta_x) - game->player.angle;
    fix_dist = distance(delta_x, delta_y) * cos(angle);
    return (fix_dist);
}
void draw_line_help(t_player *player, t_game *game, float ray_x, float ray_y, int i)
{
    float dist;
    float height;
    int start_y;
    int end;

    dist = fixed_dist(player->x, player->y, ray_x, ray_y, game);
    height = (BLOCK / dist) * (WIDTH / 2);
    start_y = (HEIGHT - height) / 2;
    end = start_y + height;
    while (start_y < end)
    {
        put_pixel(i, start_y, 255, game);
        start_y++;
        
    }
}

void draw_line(t_player *player, t_game *game, float start_x, int i)
{
    float cos_angle;
    float sin_angle;
    float ray_x;
    float ray_y;

    cos_angle = cos(start_x);
    sin_angle = sin(start_x);
    ray_x = player->x;
    ray_y = player->y;

    while (!touch(ray_x, ray_y, game))
    {
        if (debug)
            put_pixel(ray_x, ray_y, 0xFF0000, game);
        ray_x += cos_angle;
        ray_y += sin_angle;
    }
    if (!debug)
    draw_line_help(player, game, ray_x, ray_y, i);
}

int draw_loop (t_game *game)
{
    t_player *player;
    float fraction;
    float start_x;
    int i;
    
    player = &game->player;
    i = 0;
    fraction = PI / 3 / WIDTH;
    start_x = player->angle - PI / 6;
    move_player(player);
    clear_image(game);
    if (debug)
    {
        draw_square(player->x, player->y, 10, 0x00FF00, game);
        draw_map(game);
    }
    while (i < WIDTH)
    {
        draw_line(player, game, start_x, i);
        start_x += fraction;
        i++;
    }
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
    return (0); 
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