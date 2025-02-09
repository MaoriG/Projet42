/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:10:19 by mgobert           #+#    #+#             */
/*   Updated: 2025/01/24 23:29:03 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	init_image(t_data *data, char type)
{
	if (type == '1')
		data->img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, "assets/wall.xpm",
				&data->img_width, &data->img_height);
	else if (type == '0')
		data->img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, "assets/floor.xpm",
				&data->img_width, &data->img_height);
	else if (type == 'C')
		data->img_ptr = mlx_xpm_file_to_image(data->mlx_ptr,
				"assets/collect.xpm", &data->img_width, &data->img_height);
	else if (type == 'E')
		data->img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, "assets/exit.xpm",
				&data->img_width, &data->img_height);
	else if (type == 'P')
		data->img_ptr = mlx_xpm_file_to_image(data->mlx_ptr,
				"assets/player.xpm", &data->img_width, &data->img_height);
	if (!data->img_ptr)
	{
		ft_printf("Erreur : Impossible de charger l'image %c.xpm\n", type);
		return (1);
	}
	return (0);
}

int	init_window(t_data *data)
{
	if (data->map_width <= 0 || data->map_height <= 0)
	{
		ft_printf("Erro\nDimensions de la carte invalides : %d x %d\n",
			data->map_width, data->map_height);
		return (1);
	}
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
	{
		ft_printf("Error\nImpossible d'initialiser mlx.\n");
		return (1);
	}
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->map_width * 100,
			data->map_height * 100, "Map Example");
	if (!data->win_ptr)
	{
		ft_printf("Error\nImpossible de créer la fenêtre.\n");
		free(data->mlx_ptr);
		return (1);
	}
	return (0);
}

void	run_game(t_data *data)
{
	draw_map(data);
	mlx_hook(data->win_ptr, 2, 1L << 0, &handle_keypress, data);
	mlx_hook(data->win_ptr, 17, 1L << 17, &on_destroy, data);
	mlx_loop(data->mlx_ptr);
}

void	print_map(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			ft_printf("%c", data->map[y][x]);
			x++;
		}
		y++;
		ft_printf("\n");
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		ft_printf("Usage: %s <map_file>\n", argv[0]);
		return (1);
	}
	if (init_map(&data, argv[1]) != 0)
		return (1);
	ft_printf("Initial Map:\n");
	print_map(&data);
	if (init_window(&data) != 0)
		return (1);
	run_game(&data);
	return (0);
}
