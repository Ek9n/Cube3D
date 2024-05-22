/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:47:10 by jborner           #+#    #+#             */
/*   Updated: 2024/05/22 22:34:40 by hstein           ###   ########.fr       */
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

void	rotate_wheel(t_rotate *rot)
{
	rot->y = -1;
	rot->x = -1;
	while (++(rot->y) < rot->img_rot->height)
	{
		while (++(rot->x) < rot->img_rot->width)
		{
			rot->new_x = (rot->x - (*rot->img)->width / 2);
			rot->new_y = (rot->y - (*rot->img)->height / 2);
			rot->rotated_x = (rot->new_x * cos(rot->radians) - rot->new_y * \
				sin(rot->radians));
			rot->rotated_y = (rot->new_x * sin(rot->radians) + rot->new_y * \
				cos(rot->radians));
			rot->rotated_x += (*rot->img)->width / 2;
			rot->rotated_y += (*rot->img)->height / 2;
			if (rot->rotated_x >= 0 && rot->rotated_x < (*rot->img)->width && \
				rot->rotated_y >= 0 && rot->rotated_y < (*rot->img)->height)
				put_pixel_img(rot->img_rot, rot->x, rot->y, \
					get_pixel_img(*rot->img, rot->rotated_x, rot->rotated_y));
		}
		rot->x = -1;
	}
}

void	rotate_stuff(t_data *data, t_image **img, double angle, int opt)
{
	t_rotate	rot;

	rot.img = img;
	rot.radians = angle * PI / 180.0;
	rot.img_rot = create_img(data, NULL, (*img)->width, (*img)->height);
	if (opt == 1)
		rotate_wheel(&rot);
	put_img_to_img(data->texture->base_img, rot.img_rot, 500, 500);
	free_img(rot.img_rot, data->mlx);
}
