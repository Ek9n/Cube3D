/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jborner <jborner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:29:02 by hstein            #+#    #+#             */
/*   Updated: 2024/03/25 14:09:39 by jborner          ###   ########.fr       */
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
	if (data->rot[XK_Up] <= ROT_MIN)
		data->player->speed[2] = 0;
	if (data->rot[XK_Down] <= ROT_MIN)
		data->player->speed[1] = 0;
	data->player->speed[0] = (data->player->speed[2] - data->player->speed[1]) * 10;
	if (data->player->speed[0] < 0)
		data->player->speed[0] *= -1;
	// printf("cur speed: %i\n", (int)data->player->speed[0]);
}

void	move_player(t_data *data, int sign, int num)
{
	data->player->dx = sin(data->player->angle) * (1 + (((data->rot[num] * data->rot[num])) / 200));
	data->player->dy = cos(data->player->angle) * (1 + (((data->rot[num] * data->rot[num])) / 200));
	data->delay[num] %= ANIM_DELAY;
	data->delay[num] += 1;
	if (data->delay[num] != 1)
		return ;
	if (data->keys[num] && data->rot[num] < 55)
		data->rot[num] += 1;
	else if (!data->keys[num])
		data->rot[num] -= 1;
	data->player->x += data->player->dx * sign;
	data->player->y += data->player->dy * sign;
	calc_speed(data, sign);
}

void	rotate_player(t_data *data, int sign, int num)
{
	data->delay[num] %= ANIM_DELAY;
	data->delay[num] += 1;
	if (data->delay[num] != 1)
		return ;
	if (data->keys[num] && data->rot[num] < 60)
		data->rot[num] += 2;
	else if (!data->keys[num])
		data->rot[num] -= 2;
	data->player->angle += 0.1 * sign * (1 + (((data->rot[num] * data->rot[num])) / 200));
	if (data->player->angle < 0 || data->player->angle >= 2 * PI)
		data->player->angle -= 2 * PI * sign;	
	data->player->x_sin = sin(data->player->angle);
	data->player->y_cos = cos(data->player->angle);
}

void	handle_keys(t_data *data)
{
	if (data->keys[XK_Escape])
		close_game(data, NULL);
	if (data->keys[XK_Right] || data->keys[XK_d] || data->rot[XK_Right] > ROT_MIN)
		rotate_player(data, 1, XK_Right);
	if (data->keys[XK_Left] || data->keys[XK_a] || data->rot[XK_Left] > ROT_MIN)
		rotate_player(data, -1, XK_Left);
	if (data->keys[XK_Up] || data->keys[XK_w] || data->rot[XK_Up] > ROT_MIN)
		move_player(data, 1, XK_Up);
	if (data->keys[XK_Down] || data->keys[XK_s] || data->rot[XK_Down] > ROT_MIN)
		move_player(data, -1, XK_Down);
}

int	handle_keypress(int keysym, t_data *data)
{
	data->keys[keysym] = 1;
	return (0);
}

int	handle_keyrelease(int keysym, t_data *data)
{
	data->keys[keysym] = 0;
	return (0);
}

// int	handle_mouse(int button, int x, int y, t_data *data)
// {
// 	(void)x;
// 	(void)y;
// 	if (button == 1)
// 	{
// 		data->map.translate_active = !data->map.translate_active;
// 		mlx_mouse_get_pos(data->mlx_ptr, data->win_ptr,
// 			&data->mouse_x, &data->mouse_y);
// 	}
// 	return (0);
// }
