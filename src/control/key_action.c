/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_action.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 08:35:01 by yubi42            #+#    #+#             */
/*   Updated: 2024/05/15 14:52:33 by hstein           ###   ########.fr       */
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
	data->player->rev_speed = (18 - data->player->speed[0]) / 2;
	if (data->player->rev_speed < 3)
		data->player->rev_speed = 3;
	// printf("%i\n", (int)data->player->speed[0]);
		
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

void calc_rotation(t_data *data)
{
	data->player->rotation = data->rot[XK_Right] - data->rot[XK_Left];
	
}
// printf("rotation %i\n", data->player->rotation);
// printf("cur speed: %i km/h\n", (int)data->player->speed[0] * 10);

void	rotate_player(t_data *data, int sign, int num)
{
	if (!data->player->dead && data->keys[num] && data->rot[num] < ROT_MAX)
		data->rot[num] += 2;
	else if (!data->player->dead && data->keys[num]
		&& data->rot[num] >= ROT_MAX)
		data->rot[num] += 0;
	else
		data->rot[num] -= 1;
	if (data->rot[num] > ROT_MIN && (data->rot[XK_Up] > MOV_MIN
			|| data->rot[XK_Down] > MOV_MIN))
	{
		data->player->angle += (0.000003 * (data->rot[num] + (data->player->speed[0] / 1.4) + 10) * (data->rot[num] + (data->player->speed[0] / 1.4)+ 10) * data->player->rev_speed
				* data->player->rev_speed) * sign;
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

void	handle_keys(t_data *data)
{
	static int	siren = 0;
	if (data->keys[XK_Escape])
		close_game(data, NULL);
	// if (data->player->dead && data->keys[XK_y])
	if (data->keys[XK_y])
		restart_game(data, true);
	if (data->player->dead && data->keys[XK_n])
		restart_game(data, false);
	if ((data->keys[XK_Right] || data->rot[XK_Right] > ROT_MIN))
		rotate_player(data, 1, XK_Right);
	if ((data->keys[XK_Left] || data->rot[XK_Left] > ROT_MIN))
		rotate_player(data, -1, XK_Left);
	if ((data->keys[XK_Up] || data->keys[XK_w] || data->rot[XK_Up] > MOV_MIN))
		move_player(data, 1, XK_Up, XK_w);
	if ((data->keys[XK_Down] || data->keys[XK_s]
			|| data->rot[XK_Down] > MOV_MIN))
		move_player(data, -1, XK_Down, XK_s);
	if (data->keys[XK_a])
		move_side(data, -1);
	if (data->keys[XK_d])
		move_side(data, 1);
			if (data->keys[XK_h] && siren == 0)
	{
		ma_sound_start(&data->sound.siren);
		siren = 1;
	}
	else if (data->keys[XK_h] && siren == 1)
	{
		ma_sound_stop(&data->sound.siren);
		siren = 0;
	}
	calc_rotation(data);
	check_collision(data);
}
