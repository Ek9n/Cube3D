/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:29:02 by hstein            #+#    #+#             */
/*   Updated: 2024/05/06 15:22:50 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	handle_keypress(int keysym, t_data *data)
{
	if (!data->player->dead || keysym == XK_Escape || keysym == XK_y || keysym == XK_n)
		data->keys[keysym] = 1;
	return (0);
}

int	handle_keyrelease(int keysym, t_data *data)
{
	data->keys[keysym] = 0;
	return (0);
}
