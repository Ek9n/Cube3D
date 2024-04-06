/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delay.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yubi42 <yubi42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 18:17:14 by yubi42            #+#    #+#             */
/*   Updated: 2024/04/06 18:30:46 by yubi42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	delay_reset_one(int *delay, int *rot)
{
	*delay = 0;
	*rot = ROT_MIN;
}

void	delay_reset_all(int *key, int *delay, int *rot)
{
	if (delay[XK_Right] != 0 && (key[XK_Right] == 0 && key[XK_d] == 0)
		&& rot[XK_Right] <= ROT_MIN)
		delay_reset_one(&delay[XK_Right], &rot[XK_Right]);
	if (delay[XK_Left] != 0 && (key[XK_Left] == 0 && key[XK_a] == 0)
		&& rot[XK_Left] <= ROT_MIN)
		delay_reset_one(&delay[XK_Left], &rot[XK_Left]);
	if (delay[XK_Up] != 0 && (key[XK_Up] == 0 && key[XK_w] == 0)
		&& rot[XK_Up] <= ROT_MIN)
		delay_reset_one(&delay[XK_Up], &rot[XK_Up]);
	if (delay[XK_Down] != 0 && (key[XK_Down] == 0 && key[XK_s] == 0)
		&& rot[XK_Down] <= ROT_MIN)
		delay_reset_one(&delay[XK_Down], &rot[XK_Down]);
}
