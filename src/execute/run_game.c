/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:41:09 by hstein            #+#    #+#             */
/*   Updated: 2024/03/12 14:54:11 by hstein           ###   ########.fr       */
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
					mlx_put_image_to_window(data->mlx, data->mlx_win, data->texture->ea->addr, col * IMG_SIZE, row * IMG_SIZE);
				else if (z == 1 && data->map->grid[row][col] == 1)
					mlx_put_image_to_window(data->mlx, data->mlx_win, data->texture->so->addr, col * IMG_SIZE, row * IMG_SIZE);
				else if (z == 2 && data->map->grid[row][col] == 2)
					mlx_put_image_to_window(data->mlx, data->mlx_win, data->texture->no->addr, col * IMG_SIZE, row * IMG_SIZE);
			}
			col = -1;
		}
		row = -1;
		z++;
	}
}

// void destroy_textures(t_data *data)
// {
// 	if (data->texture->no_addr)
// 		mlx_destroy_image(data->mlx, data->texture->no_addr);
// 	if (data->texture->so_addr)
// 		mlx_destroy_image(data->mlx, data->texture->so_addr);
// 	if (data->texture->we_addr)
// 		mlx_destroy_image(data->mlx, data->texture->we_addr);
// 	if (data->texture->ea_addr)
// 		mlx_destroy_image(data->mlx, data->texture->ea_addr);
// }

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->bytes_per_line + x * (img->bpp / 8));
	*(int *)pixel = color;
}

// void	put_pixel_img(t_img *img, int x, int y, int color)
// {
// 	char	*dst;

// 	if (color == (int)0xFF000000)
// 		return ;
// 	if (x >= 0 && y >= 0 && x < img->width && y < img->height) {
// 		dst = img->addr + (y * img->bytes_per_line + x * (img->bpp / 8));
// 		*(unsigned int *) dst = color;
// 	}
// }

// unsigned int	get_pixel_img(t_img *img, int x, int y) {
// 	return (*(unsigned int *)((img->addr
// 			+ (y * img->bytes_per_line) + (x * img->bpp / 8))));
// }

// void	put_img_to_img(t_img *dst, t_img *src, int x, int y) {
// 	int i;
// 	int j;

// 	i = 0;
// 	while(i < src->width) {
// 		j = 0;
// 		while (j < src->height) {
// 			put_pixel_img(dst, x + i, y + j, get_pixel_img(src, i, j));
// 			j++;
// 		}
// 		i++;
// 	}
// }
void	put_pixel_img(t_img img, int x, int y, int color)
{
	char	*dst;

	if (color == (int)0x333333)
		return ;
	if (x >= 0 && y >= 0 && x < img.width && y < img.height) {
		dst = img.addr + (y * img.bytes_per_line + x * (img.bpp / 8));
		*(unsigned int *) dst = color;
	}
}

unsigned int	get_pixel_img(t_img img, int x, int y) {
	return (*(unsigned int *)((img.addr
			+ (y * img.bytes_per_line) + (x * img.bpp / 8))));
}

void	put_img_to_img(t_img dst, t_img src, int x, int y) {
	int i;
	int j;

	i = 0;
	while(i < src.width) {
		j = 0;
		while (j < src.height) {
			put_pixel_img(dst, x + i, y + j, get_pixel_img(src, i, j));
			j++;
		}
		i++;
	}
}
void	run_game(t_data *data)
{
	mlx_init_game(data);
	printf("(run_game) hi :-) width:%d, height:%d\n", data->width, data->height);

	print_grid(data->map);

	data->texture->base_img = create_img(data, NULL, data->width, data->height);
	data->texture->img1 = create_img(data, NULL, 64, 64);
	// create_minimap(data);

// Make img green:
	for (int y = 0; y < data->width; y++)
	{
		for (int x = 0; x < data->height; x++)
			img_pix_put(data->texture->base_img, y, x, GREEN);
	}

	// for (int y = 0; y < IMG_SIZE; y++)
	// {
	// 	for (int x = 0; x < IMG_SIZE; x++)
	// 		img_pix_put(data->texture->img1, y, x, PURPLE);
	// }
	// img_pix_put(data->texture->base_img, 100, 63, PURPLE);
/* 	img_pix_put(data->texture->img1, 32, 32, PURPLE); */
	
	put_img_to_img(*data->texture->base_img, *data->texture->ea, 0, 0);

	mlx_put_image_to_window(data->mlx, data->mlx_win, data->texture->base_img->img_ptr, 0, 0);

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
