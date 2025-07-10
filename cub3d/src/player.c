/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:05:53 by mgobert           #+#    #+#             */
/*   Updated: 2025/07/10 18:13:54 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void init_player(t_player *player, t_game *game)
{
    char ** mapcopy;
    int map_x;
    int map_y;

    if (find_player(game))
        ft_error("Joueur non trouve");
    map_x = game->player.x / BLOCK;
    map_y = game->player.y / BLOCK;
    if (!(mapcopy = copy_map(game->map, game->map_height)))
        ft_error("Erreur copie de la map");
    if (flood_fill_check(mapcopy, map_x, map_y))
    {
        clean_map(game, mapcopy);
        ft_error("Error map");
    }
    player->angle = PI / 2;
    player->key_up = false;
    player->key_down = false;
    player->key_left = false;
    player->key_right = false;
    player->left_rotate = false;
    player->right_rotate = false;
}
char **copy_map(char **map, int height)
{
    char **copy;
    int i;
    
    i = 0;
    copy = ft_calloc(sizeof(char *), height + 1);
    if (!copy)
        return (NULL);
    while (i < height)
    {
        copy[i] = ft_strdup(map[i]);
        if (!copy[i])
        {
            while (--i >= 0)
                free(copy[i]);
            free(copy);
            return (NULL);
        }
        i++;
    }
    return (copy);
}
void clean_map(t_game *game, char **map)
{
    int i;

    i = 0;
    while(i < game->map_height)
    {
        free(map[i]);
        i++;
    }
    free(map);
}

int key_press(int keycode, t_player *player)
{
    if(keycode == W)
        player->key_up = true;
    if(keycode == S)
        player->key_down = true;
    if(keycode == A)
        player->key_left = true;
    if(keycode == D)
        player->key_right = true;
    if (keycode == LEFT)
        player->left_rotate = true;
    if (keycode == RIGHT)
        player->right_rotate = true;
    return (0);
}

int key_release(int keycode, t_player *player)
{
    if(keycode == W)
        player->key_up = false;
    if(keycode == S)
        player->key_down = false;
    if(keycode == A)
        player->key_left = false;
    if(keycode == D)
        player->key_right = false;
    if (keycode == LEFT)
        player->left_rotate = false;
    if (keycode == RIGHT)
        player->right_rotate = false;
    return (0);
}
void move_player(t_player *player)
{
    int speed;
    float angle_speed;
    float cos_angle;
    float sin_angle;

    speed = 3;
    angle_speed = 0.03;
    cos_angle = cos(player->angle);
    sin_angle = sin(player->angle);
    if (player->left_rotate)
        player->angle -= angle_speed;
    if (player->right_rotate)
        player->angle += angle_speed;
    if (player->angle > 2 * PI)
        player->angle = 0;
    if (player->angle < 0)
        player->angle = 2 * PI;
    if (player->key_up || player->key_down || player->key_left || player->key_right)
        move_player_help(player, speed, cos_angle, sin_angle);
}

void move_player_help(t_player *player, int speed, float cos_angle, float sin_angle)
{
    
    if (player->key_up)
    {
        player->x += cos_angle * speed;
        player->y += sin_angle * speed;
    }
    if (player->key_down)
    {
        player->x -= cos_angle * speed;
        player->y -= sin_angle * speed;
    }
    if (player->key_left)
    {
        player->x += sin_angle * speed;
        player->y -= cos_angle * speed;
    }
    if (player->key_right)
    {
        player->x -= sin_angle * speed;
        player->y += cos_angle * speed;
    }
}
int	find_player(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
    while (game->map[0][game->map_width])
		game->map_width++;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'N')
			{
				game->player.x = x * BLOCK;
				game->player.y = y * BLOCK;
                game->map[y][x] = '0';
				return (0);
			}
			x++;
		}
		y++;
	}
    printf("player not found");
	return (1);
}