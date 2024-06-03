/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:29:02 by hstein            #+#    #+#             */
/*   Updated: 2024/06/03 16:43:35 by hstein           ###   ########.fr       */
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

int	destroy_window(t_data *data)
{
	close_game(data, NULL);
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
