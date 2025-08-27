/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 17:07:56 by mgobert           #+#    #+#             */
/*   Updated: 2025/08/26 18:14:26 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	move_forward(t_move *ctx)
{
	float	nx;
	float	ny;

	nx = ctx->player->x + ctx->cos_a * ctx->speed;
	ny = ctx->player->y + ctx->sin_a * ctx->speed;
	if (!is_wall(nx, ctx->player->y, ctx->game))
		ctx->player->x = nx;
	if (!is_wall(ctx->player->x, ny, ctx->game))
		ctx->player->y = ny;
}

static void	move_backward(t_move *ctx)
{
	float	nx;
	float	ny;

	nx = ctx->player->x - ctx->cos_a * ctx->speed;
	ny = ctx->player->y - ctx->sin_a * ctx->speed;
	if (!is_wall(nx, ctx->player->y, ctx->game))
		ctx->player->x = nx;
	if (!is_wall(ctx->player->x, ny, ctx->game))
		ctx->player->y = ny;
}

static void	strafe_left(t_move *ctx)
{
	float	nx;
	float	ny;

	nx = ctx->player->x + ctx->sin_a * ctx->speed;
	ny = ctx->player->y - ctx->cos_a * ctx->speed;
	if (!is_wall(nx, ctx->player->y, ctx->game))
		ctx->player->x = nx;
	if (!is_wall(ctx->player->x, ny, ctx->game))
		ctx->player->y = ny;
}

static void	strafe_right(t_move *ctx)
{
	float	nx;
	float	ny;

	nx = ctx->player->x - ctx->sin_a * ctx->speed;
	ny = ctx->player->y + ctx->cos_a * ctx->speed;
	if (!is_wall(nx, ctx->player->y, ctx->game))
		ctx->player->x = nx;
	if (!is_wall(ctx->player->x, ny, ctx->game))
		ctx->player->y = ny;
}

void	move_player_help(t_move *ctx)
{
	if (ctx->player->key_up)
		move_forward(ctx);
	if (ctx->player->key_down)
		move_backward(ctx);
	if (ctx->player->key_left)
		strafe_left(ctx);
	if (ctx->player->key_right)
		strafe_right(ctx);
}
