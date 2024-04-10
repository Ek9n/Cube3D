/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:41:09 by hstein            #+#    #+#             */
/*   Updated: 2024/04/10 16:43:54 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	run_game(t_data *data)
{
	mlx_init_game(data);
	printf("(run_game) hi :-) width:%d, height:%d\n", data->width,
		data->height);
	print_grid(data->map);
	data->texture->base_img = create_img(data, NULL, data->width, data->height);
	create_minimap(data);
	render(data);
	printf("rows:%d, cols:%d\n", data->map->row_max, data->map->col_max);

	// create_img(data, "./img/carframe.xmp", 0, 0);
data->texture->steeringwheel = create_img(data, "./img/steeringwheel.xpm", 129, 129);
data->texture->steeringwheel2 = create_img(data, "./img/steeringwheel.xpm", 129, 129);
data->texture->carframe = create_img(data, "./img/carframe.xpm", 1000, 563);
data->texture->carframe2 = resize_img(data, &data->texture->carframe, data->width, data->height);
	mlx_loop_hook(data->mlx, &render, data);
	mlx_hook(data->mlx_win, KeyPress, KeyPressMask, &handle_keypress, data);
	mlx_hook(data->mlx_win, KeyRelease, KeyReleaseMask, &handle_keyrelease, data);
	mlx_loop(data->mlx);
}

/*
	void	img_pix_put(t_img *img, int x, int y, int clr)
	{
		char	*pixel;

		pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
		*(int *)pixel = clr;
	}


		mlx_loop_hook(data.mlx_ptr, &render, &data);
		mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
		mlx_mouse_hook(data.win_ptr, &handle_mouse, &data);
		mlx_hook(data.win_ptr, 17, 1L << 17, close_window, &data);
		mlx_loop(data.mlx_ptr);


	mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
	mlx_destroy_window(data.mlx_ptr, data.win_ptr);
	mlx_destroy_display(data.mlx_ptr);
*/
