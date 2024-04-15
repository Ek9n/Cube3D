/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delay.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yubi42 <yubi42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 18:17:14 by yubi42            #+#    #+#             */
/*   Updated: 2024/04/15 16:58:20 by yubi42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	delay_reset_one(int *delay, int *rot, int rot_value)
{
	*delay = 0;
	*rot = rot_value;
}

void	delay_reset_all(int *key, int *delay, int *rot)
{
	if (delay[XK_Right] != 0 && (key[XK_Right] == 0)
		&& rot[XK_Right] <= ROT_MIN)
		delay_reset_one(&delay[XK_Right], &rot[XK_Right], ROT_MIN);
	if (delay[XK_Left] != 0 && (key[XK_Left] == 0)
		&& rot[XK_Left] <= ROT_MIN)
		delay_reset_one(&delay[XK_Left], &rot[XK_Left], ROT_MIN);
	if (delay[XK_Up] != 0 && (key[XK_Up] == 0 && key[XK_w] == 0)
		&& rot[XK_Up] <= ROT_MIN)
		delay_reset_one(&delay[XK_Up], &rot[XK_Up], MOV_MIN);
	if (delay[XK_Down] != 0 && (key[XK_Down] == 0 && key[XK_s] == 0)
		&& rot[XK_Down] <= ROT_MIN)
		delay_reset_one(&delay[XK_Down], &rot[XK_Down], MOV_MIN);
	if (delay[XK_a] != 0 && key[XK_a] == 0)
		delay_reset_one(&delay[XK_a], &rot[XK_a], 0);
	if (delay[XK_d] != 0 && key[XK_d] == 0)
		delay_reset_one(&delay[XK_d], &rot[XK_d], 0);
}
