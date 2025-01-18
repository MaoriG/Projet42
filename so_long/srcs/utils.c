/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 21:52:04 by mgobert           #+#    #+#             */
/*   Updated: 2025/01/18 17:40:29 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

/* void cleanup(t_data *data)
{
    if (data->img_ptr)
        mlx_destroy_image(data->mlx_ptr, data->img_ptr);
    if (data->win_ptr)
        mlx_destroy_window(data->mlx_ptr, data->win_ptr);
    if (data->mlx_ptr)
        free(data->mlx_ptr);
} */
/* void manage_init(t_data *data, char c)
{
    if (data == NULL)
    {
        printf("Erreur : Le pointeur 'data' est NULL.\n");
        return;
    }

    if (c == '1')
        init_image(data, '1');
    else if (c == '0')
        init_image(data, '0');
    else if (c == 'C')
        init_image(data, 'C');
    else if (c == 'E')
        init_image(data, 'E');
    else if (c == 'P')
        init_image(data, 'P');
    else
    {
        printf("Erreur : Type d'image inconnu dans manage_init %c\n", c);
    }
} */
