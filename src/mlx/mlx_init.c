/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/04/26 15:54:46 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "cube.h"

void	init_img(t_image *img)
{
	img->addr = NULL;
	img->img_ptr = NULL;
}

t_image	*create_img(t_data *data, char *path, int w, int h)
{
	t_image	*img;

	img = NULL;
	img = malloc(sizeof(t_image));
	if (!img)
		close_game(data, "Not able to allocate memory or wrong img path");
	init_img(img);
	if (path)
		img->img_ptr = mlx_xpm_file_to_image(data->mlx, path, &(img->width),
				&(img->height));
	else
	{
		img->img_ptr = mlx_new_image(data->mlx, w, h);
		img->width = w;
		img->height = h;
	}
	img->addr = mlx_get_data_addr(img->img_ptr, &(img->bpp),
			&(img->bytes_per_line), &(img->endian));
	if (!(img->img_ptr || img->addr))
		close_game(data, "Not able to allocate memory for img_ptr or addr");
	return (img);
}

void	create_wall_imgs(t_data *data)
{
	data->texture->no = create_img(data, data->texture->no_path, 0, 0);
	data->texture->so = create_img(data, data->texture->so_path, 0, 0);
	data->texture->we = create_img(data, data->texture->we_path, 0, 0);
	data->texture->ea = create_img(data, data->texture->ea_path, 0, 0);
	if (data->texture->ea->width != IMG_SIZE)
	{
		resize_same_img(data, &data->texture->no, IMG_SIZE, IMG_SIZE);
		resize_same_img(data, &data->texture->so, IMG_SIZE, IMG_SIZE);
		resize_same_img(data, &data->texture->we, IMG_SIZE, IMG_SIZE);
		resize_same_img(data, &data->texture->ea, IMG_SIZE, IMG_SIZE);
	}
}

void	mlx_init_game(t_data *data)
{
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		close_game(data, "ERROR");
	data->mlx_win = mlx_new_window(data->mlx, data->width, data->height,
			"cub3d");
	if (data->mlx_win == NULL)
		close_game(data, "ERROR");
	create_wall_imgs(data);
	data->texture->black = create_img(data, "./img/black.xpm", 0, 0);
	data->texture->steeringwheel = create_img(data, "./img/steeringwheel.xpm",
				0, 0);
	data->texture->steeringwheel2 = create_img(data, "./img/steeringwheel.xpm",
				0, 0);
	data->texture->carframe = create_img(data, "./img/cockpit.xpm", 0, 0);
	data->texture->carframe2 = resize_img(data, &data->texture->carframe,
			data->width, data->height);
	data->texture->nums = create_img(data, "./img/nums.xpm", 0, 0);
	data->texture->numshadow = create_img(data, "./img/numshadow.xpm", 0, 0);
	data->texture->game_over = create_img(data, "./img/game_over2.xpm", 0, 0);
	resize_same_img(data, &data->texture->game_over, data->width, data->height);
	setup_sounds(data);
}
