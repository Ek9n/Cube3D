/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_player_img.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jborner <jborner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:47:10 by jborner           #+#    #+#             */
/*   Updated: 2024/05/15 15:52:23 by jborner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

double	calc_old_x(t_data *data, t_image **old, int x, int y)
{
	return ((x - (*old)->width / 2) * data->player->y_cos + (y - (*old)->height
			/ 2) * data->player->x_sin + (*old)->width / 2);
}

double	calc_old_y(t_data *data, t_image **old, int x, int y)
{
	return (-(x - (*old)->width / 2) * data->player->x_sin + (y - (*old)->height
			/ 2) * data->player->y_cos + (*old)->height / 2);
}

void	rotate_player_img(t_data *data, t_image **old, t_image **new)
{
	int		x;
	int		y;
	double	old_x;
	double	old_y;

	if (*new)
		free_img(*new, data->mlx);
	*new = create_img(data, NULL, (*old)->width, (*old)->height);
	y = 0;
	while (y < (*old)->height)
	{
		x = 0;
		while (x < (*old)->width)
		{
			old_x = calc_old_x(data, old, x, y);
			old_y = calc_old_y(data, old, x, y);
			if (old_x >= 0 && old_x < (*old)->width && old_y >= 0
				&& old_y < (*old)->height)
				put_pixel_img(*new, x, y, get_pixel_img(*old, old_x, old_y));
			x++;
		}
		y++;
	}
}
