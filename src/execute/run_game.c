/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jborner <jborner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:41:09 by hstein            #+#    #+#             */
/*   Updated: 2024/06/03 15:20:08 by jborner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	start_counter(t_data *data)
{
	unsigned int	i;

	i = 3;
	while (i > 0)
	{
		if (data->sound_on)
			ma_sound_set_pitch(&data->sound.motor, data->player->speed[0] / 8);
		render_background(data, data->texture->base_img);
		render_background(data, data->texture->base_img2);
		render_minimap(data, data->texture->minimap);
		put_img_to_img(data->texture->base_img, data->texture->carframe2, 0, 0);
		put_img_to_img(data->texture->base_img, data->texture->minimap->resize,
			1400, 650);
		rotate_stuff(data, &data->texture->steeringwheel, -4
			* data->player->rotation, 1);
		render_backmirror(data);
		put_single_num(data, i, 1000, 250);
		mlx_put_image_to_window(data->mlx, data->mlx_win,
			data->texture->base_img->img_ptr, 0, 0);
		fps_delay(1);
		--i;
	}
}

void	run_game(t_data *data)
{
	mlx_init_game(data);
	print_grid(data->map);
	data->texture->base_img = create_img(data, NULL, data->width, data->height);
	data->texture->base_img2 = create_img(data, NULL, data->width,
			data->height);
	data->texture->base_img2_resize = create_img(data, NULL, data->width,
			data->height);
	create_minimap(data);
	start_counter(data);
	mlx_loop_hook(data->mlx, &render, data);
	mlx_hook(data->mlx_win, KeyPress, KeyPressMask, &handle_keypress, data);
	mlx_hook(data->mlx_win, KeyRelease, KeyReleaseMask, &handle_keyrelease,
		data);
	mlx_hook(data->mlx_win, DestroyNotify, NoEventMask, &destroy_window, data);
	mlx_loop(data->mlx);
}
