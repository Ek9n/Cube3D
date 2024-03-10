/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:29:02 by hstein            #+#    #+#             */
/*   Updated: 2024/03/10 15:07:57 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	handle_keypress(int keysym, t_data *data)
{
	(void)data;
	if (keysym == XK_Escape)
	{
		close_game(data, NULL);
	}
	if (keysym == XK_Up)
		data->player->x -= 1.5;
	if (keysym == XK_Down)
		data->player->x += 1.5;
	if (keysym == XK_Left)
		data->player->y -= 1.5;
	if (keysym == XK_Right)
		data->player->y += 1.5;
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
