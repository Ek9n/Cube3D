/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jborner <jborner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:29:02 by hstein            #+#    #+#             */
/*   Updated: 2024/05/15 15:35:52 by jborner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	handle_keypress(int keysym, t_data *data)
{
	if (!data->player->dead || keysym == XK_Escape || keysym == XK_y
		|| keysym == XK_n)
		data->keys[keysym] = 1;
	return (0);
}

int	handle_keyrelease(int keysym, t_data *data)
{
	data->keys[keysym] = 0;
	return (0);
}

void	handle_sound_keys(t_data *data)
{
	if (data->keys[XK_h] && data->siren == 0)
	{
		ma_sound_start(&data->sound.siren);
		data->siren = 1;
	}
	else if (data->keys[XK_h] && data->siren == 1)
	{
		ma_sound_stop(&data->sound.siren);
		data->siren = 0;
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
	handle_sound_keys(data);
	data->player->rotation = data->rot[XK_Right] - data->rot[XK_Left];
	check_collision(data);
}
