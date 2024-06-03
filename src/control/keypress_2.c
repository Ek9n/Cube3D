/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:29:02 by hstein            #+#    #+#             */
/*   Updated: 2024/06/03 16:43:39 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	handle_directions(t_data *data)
{
	if (!(data->keys[XK_Right] && data->keys[XK_Left]))
	{
		if ((data->keys[XK_Right] || data->rot[XK_Right] > ROT_MIN))
			data->rot[XK_Right] -= 1;
		if ((data->keys[XK_Left] || data->rot[XK_Left] > ROT_MIN))
			data->rot[XK_Left] -= 1;
		if ((data->keys[XK_Right]))
			rotate_player(data, 1, XK_Right);
		if ((data->keys[XK_Left]))
			rotate_player(data, -1, XK_Left);
	}
}

void	handle_keys(t_data *data)
{
	if (data->keys[XK_Escape])
		close_game(data, NULL);
	if (data->keys[XK_y])
		restart_game(data, true);
	if (data->player->dead && data->keys[XK_n])
		restart_game(data, false);
	handle_directions(data);
	if ((data->keys[XK_Up] || data->keys[XK_w] || data->rot[XK_Up] > MOV_MIN))
		move_player(data, 1, XK_Up, XK_w);
	if ((data->keys[XK_Down] || data->keys[XK_s]
			|| data->rot[XK_Down] > MOV_MIN))
		move_player(data, -1, XK_Down, XK_s);
	if (data->keys[XK_a])
		move_side(data, -1);
	if (data->keys[XK_d])
		move_side(data, 1);
	if (data->sound_on)
		handle_sound_keys(data);
	data->player->rotation = data->rot[XK_Right] - data->rot[XK_Left];
	check_collision(data);
}
