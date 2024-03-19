/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yubi42 <yubi42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:29:02 by hstein            #+#    #+#             */
/*   Updated: 2024/03/19 14:12:34 by yubi42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void move_player(t_data *data, int sign)
{
	data->player->x += data->player->dx * sign;
	data->player->y += data->player->dy * sign;
}

void rotate_player(t_data *data, int sign)
{
		data->player->angle += 0.1 * sign;
		if(data->player->angle < 0 || data->player->angle >= 2 * PI)
			data->player->angle += 2 * PI * sign;
		data->player->dx = sin(data->player->angle) * MOVSPEED;
		data->player->dy = cos(data->player->angle) * MOVSPEED;
}

int	handle_keypress(int keysym, t_data *data)
{
	(void)data;
	if (keysym == XK_Escape)
		close_game(data, NULL);
	if (keysym == XK_Up || keysym == XK_w)
		move_player(data, 1);
	if (keysym == XK_Down || keysym == XK_s)
		move_player(data, -1);
	if (keysym == XK_Left || keysym == XK_a)
		rotate_player(data, -1);
	if (keysym == XK_Right || keysym == XK_d)
		rotate_player(data, 1);
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
