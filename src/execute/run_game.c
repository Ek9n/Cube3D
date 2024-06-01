/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:41:09 by hstein            #+#    #+#             */
/*   Updated: 2024/06/02 01:03:58 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	run_game(t_data *data)
{
	mlx_init_game(data);
	print_grid(data->map);
	data->texture->base_img = create_img(data, NULL, data->width, data->height);
	data->texture->base_img2 = create_img(data, NULL, data->width, data->height);
	data->texture->base_img2_resize = create_img(data, NULL, data->width, data->height);
	create_minimap(data);
	mlx_loop_hook(data->mlx, &render, data);
	mlx_hook(data->mlx_win, KeyPress, KeyPressMask, &handle_keypress, data);
	mlx_hook(data->mlx_win, KeyRelease, KeyReleaseMask, &handle_keyrelease,
		data);
	mlx_hook(data->mlx_win, DestroyNotify, NoEventMask, &destroy_window, data);
	mlx_loop(data->mlx);
}
