/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 16:13:54 by mgobert           #+#    #+#             */
/*   Updated: 2025/06/28 17:27:59 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}
int close_win (t_vars *vars)
{
    mlx_destroy_window(vars->mlx, vars->win);
    exit(0);
}
int keyclose (int keycode, t_vars *vars)
{
    if (keycode == 65307)
    {
        mlx_destroy_window(vars->mlx, vars->win);
        exit(0);
    }
    return (0);
}
int	main(void)
{
	t_vars vars;
	t_data img;

	vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Cub3d");
	img.img = mlx_new_image(vars.mlx, 1920, 1080);
    mlx_hook(vars.win, 2, 1L<<0, keyclose, &vars);
    mlx_hook(vars.win, 17, 0, close_win, &vars);
    mlx_loop(vars.mlx);
}