/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:41:09 by hstein            #+#    #+#             */
/*   Updated: 2024/03/06 14:45:20 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void    create_minimap(t_data *data)
{
	int col;
	int row;
	int	z;

	z = 0;
	col = -1;
	row = -1;

	while (z < 3)
	{
		while(++row < data->map->row_max)
		{
			while(++col < data->map->col_max)
			{
				if (z == 0 && data->map->grid[row][col] == 0)
					mlx_put_image_to_window(data->mlx, data->mlx_win, data->texture->ea_addr, col * IMG_SIZE, row * IMG_SIZE);
				else if (z == 1 && data->map->grid[row][col] == 1)
					mlx_put_image_to_window(data->mlx, data->mlx_win, data->texture->so_addr, col * IMG_SIZE, row * IMG_SIZE);
				else if (z == 2 && data->map->grid[row][col] == 2)
					mlx_put_image_to_window(data->mlx, data->mlx_win, data->texture->no_addr, col * IMG_SIZE, row * IMG_SIZE);
			}
			col = -1;
		}
		row = -1;
		z++;
	}
}

void destroy_textures(t_data *data)
{
	if (data->texture->no_addr)
		mlx_destroy_image(data->mlx, data->texture->no_addr);
	if (data->texture->so_addr)
		mlx_destroy_image(data->mlx, data->texture->so_addr);
	if (data->texture->we_addr)
		mlx_destroy_image(data->mlx, data->texture->we_addr);
	if (data->texture->ea_addr)
		mlx_destroy_image(data->mlx, data->texture->ea_addr);
}

// void    create_minimap(t_texture *textures)
// {

// 	mlx_put_image_to_window(data->mlx, data->mlx_win, data->texture->no_addr, col * IMG_SIZE, row * IMG_SIZE);

// }

// void	img_pix_put(t_texture *, int x, int y, int clr)
// {
// 	char	*pixel;

// 	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
// 	*(int *)pixel = clr;
// }

/*
typedef struct	s_img
{
	XImage			*image;
	Pixmap			pix;
	GC				gc;
	int				size_line;
	int				bpp;
	int				width;
	int				height;
	int				type;
	int				format;
	char			*data;
	XShmSegmentInfo	shm;
}				t_img;
*/

void	run_game(t_data *data)
{
	printf("(run_game) hi :-)\n");
	mlx_init_game(data);

	print_grid(data->map);
	create_minimap(data);
	// destroy_textures(data);
	// create_minimap(data);
	// data->texture->img_map_ground = mlx_new_image(data->mlx, IMG_SIZE, IMG_SIZE);
	// data->texture->map_ground = mlx_get_data_addr(data->texture->img_map_ground, &data->texture->no_addr->bpp, &data->texture->no_addr->line_len, &data->texture->no_addr->endian);

	// printf("bpp: %d\n", data->texture->no_addr->bpp);

	printf("rows:%d, cols:%d\n", data->map->row_max, data->map->col_max);
	mlx_hook(data->mlx_win, KeyPress, KeyPressMask, &handle_keypress, data);
	// mlx_hook(data->mlx_win, KeyRelease, KeyReleaseMask, &handle_keyrelease, data);

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