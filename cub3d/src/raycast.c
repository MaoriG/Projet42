/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 18:31:39 by mgobert           #+#    #+#             */
/*   Updated: 2025/07/10 18:41:17 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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