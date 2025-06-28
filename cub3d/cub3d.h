/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 16:07:30 by mgobert           #+#    #+#             */
/*   Updated: 2025/06/28 17:12:51 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H

# include "./minilibx/mlx.h"
# include "./minilibx/mlx_int.h"
# include "stdbool.h"
# include "string.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdio.h>
# include <stdlib.h>

enum 
{
    ON_KEYDOWN = 2,
    ON_KEYUP = 3,
    ON_MOUSEDOWN = 4,
    ON_MOUSEUP = 5,
    ON_MOUSEMOVE = 6,
    ON_EXPOSE = 12,
    ON_DESTROY = 17
};

typedef struct s_vars
{
    void *mlx;
    void *win;
}       t_vars;

typedef struct s_data 
{
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;    
}   t_data;

#endif