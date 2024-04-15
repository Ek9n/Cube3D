/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delay.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yubi42 <yubi42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 18:17:14 by yubi42            #+#    #+#             */
/*   Updated: 2024/04/15 19:44:39 by yubi42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"


int check_delay(t_data *data, int num1, int num2, int min)
{
	if (data->keys[num1] == 0 && data->keys[num2] == 0 && data->rot[num1] <= min && data->rot[num2] <= min)
		return (1);
	return (0);
}

void	delay_reset_all(t_data *data/* , int *key, int *rot */)
{
	if (data->delay_rot && check_delay(data, XK_Right, XK_Left, ROT_MIN) && check_delay(data, XK_Up, XK_Down, MOV_MIN) && check_delay(data, XK_a, XK_d, 0))
		data->delay_rot = 0;
}
