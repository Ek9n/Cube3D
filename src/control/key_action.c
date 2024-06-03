/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_action.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 08:35:01 by yubi42            #+#    #+#             */
/*   Updated: 2024/06/03 16:47:40 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	calc_speed(t_data *data, int sign)
{
	if (sign < 0)
		data->player->speed[1] = sqrt((data->player->dx * data->player->dx)
				+ (data->player->dy * data->player->dy));
	else
		data->player->speed[2] = sqrt((data->player->dx * data->player->dx)
				+ (data->player->dy * data->player->dy));
	if (data->rot[XK_Up] <= MOV_MIN)
		data->player->speed[2] = 0;
	if (data->rot[XK_Down] <= MOV_MIN)
		data->player->speed[1] = 0;
	data->player->speed[0] = (data->player->speed[2] - data->player->speed[1]);
	if (data->player->speed[0] < 0)
		data->player->speed[0] *= -1;
	data->player->rev_speed = 18 - data->player->speed[0];
	if (data->player->rev_speed < 3)
		data->player->rev_speed = 3;
}

void	move_player(t_data *data, int sign, int num, int other_num)
{
	if (!data->player->dead && (data->keys[num] || data->keys[other_num])
		&& data->rot[num] < MOV_MAX)
		data->rot[num] += 1;
	else
		data->rot[num] -= 1;
	if (data->rot[num] > MOV_MIN)
	{
		data->player->dx = sin(data->player->angle) * (1 + (((data->rot[num]
							* data->rot[num])) / 200));
		data->player->dy = cos(data->player->angle) * (1 + (((data->rot[num]
							* data->rot[num])) / 200));
		data->player->x += data->player->dx * sign;
		data->player->y += data->player->dy * sign;
	}
	calc_speed(data, sign);
}

void	rotate_player(t_data *data, int sign, int num)
{
	float	rotspeed;

	if (!data->player->dead && data->keys[num] && data->rot[num] < ROT_MAX)
		data->rot[num] += 2;
	else if (!data->player->dead && data->keys[num]
		&& data->rot[num] >= ROT_MAX)
		data->rot[num] += 0;
	if (data->rot[num] > ROT_MIN && (data->rot[XK_Up] > MOV_MIN
			|| data->rot[XK_Down] > MOV_MIN))
	{
		if (data->player->speed[0] < 5)
			rotspeed = (0.15 - 0.004 * data->player->rev_speed) * sign;
		else
			rotspeed = (0.15 - (0.002 * data->player->speed[0])) * sign;
		if ((sign > 0 && rotspeed < 0) || (sign < 0 && rotspeed > 0))
			rotspeed = 0;
		data->player->angle += rotspeed;
		if (data->player->angle < 0 || data->player->angle >= 2 * PI)
			data->player->angle -= 2 * PI * sign;
		data->player->x_sin = sin(data->player->angle);
		data->player->y_cos = cos(data->player->angle);
	}
}

void	move_side(t_data *data, int sign)
{
	data->player->x += sin(data->player->angle + (0.5 * PI * sign)) * SIDESTEP;
	data->player->y += cos(data->player->angle + (0.5 * PI * sign)) * SIDESTEP;
}

void	restart_game(t_data *data, bool opt)
{
	if (opt)
		data->restart = true;
	else
		data->restart = false;
	mlx_loop_end(data->mlx);
}
