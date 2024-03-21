/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yubi42 <yubi42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:29:02 by hstein            #+#    #+#             */
/*   Updated: 2024/03/21 20:30:47 by yubi42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	move_player(t_data *data, int sign, int num)
{
	data->player->dx = sin(data->player->angle) * MOVSPEED * (1
		+ ((data->rot[num] * data->rot[num]) / 200));
	data->player->dy = cos(data->player->angle) * MOVSPEED * (1
		+ ((data->rot[num] * data->rot[num]) / 200));
	data->delay[num] %= ROT_DELAY;
	data->delay[num] += 1;
	if (data->delay[num] != 1)
		return ;
	if (data->keys[num])
		data->rot[num] += 1;
	else
		data->rot[num] -= 1;
	data->player->x += data->player->dx * sign;
	data->player->y += data->player->dy * sign;
}

void	rotate_player(t_data *data, int sign, int num)
{
	data->delay[num] %= ROT_DELAY;
	data->delay[num] += 1;
	if (data->delay[num] != 1)
		return ;
	if (data->keys[num])
		data->rot[num] += 1;
	else
		data->rot[num] -= 1;
	data->player->angle += 0.1 * sign * (1 + ((data->rot[num] * data->rot[num])
			/ 500));
	if (data->player->angle < 0 || data->player->angle >= 2 * PI)
		data->player->angle += 2 * PI * sign;
	data->player->x_sin = sin(data->player->angle);
	data->player->y_cos = cos(data->player->angle);
}

void	handle_keys(t_data *data)
{
	if (data->keys[XK_Escape])
		close_game(data, NULL);
	if (data->keys[XK_Right] || data->keys[XK_d] || data->rot[XK_Right])
		rotate_player(data, 1, XK_Right);
	if (data->keys[XK_Left] || data->keys[XK_a] || data->rot[XK_Left])
		rotate_player(data, -1, XK_Left);
	if (data->keys[XK_Up] || data->keys[XK_w] || data->rot[XK_Up])
		move_player(data, 1, XK_Up);
	if (data->keys[XK_Down] || data->keys[XK_s] || data->rot[XK_Down])
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
