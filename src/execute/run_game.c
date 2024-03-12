/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:41:09 by hstein            #+#    #+#             */
/*   Updated: 2024/03/12 17:56:28 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"


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

void	put_pixel_img(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (color == (int)0x000000)
		return ;
	if (x >= 0 && y >= 0 && x < img->width && y < img->height) {
		dst = img->addr + (y * img->bytes_per_line + x * (img->bpp / 8));
		*(unsigned int *) dst = color;
	}
}

unsigned int	get_pixel_img(t_img *img, int x, int y) {
	return (*(unsigned int *)((img->addr
			+ (y * img->bytes_per_line) + (x * img->bpp / 8))));
}

void	put_img_to_img(t_img *dst, t_img *src, int x, int y) {
	int i;
	int j;

	i = 0;
	while(i < src->width) {
		j = 0;
		while (j < src->height) {
			put_pixel_img(dst, x + i, y + j, get_pixel_img(src, i, j));
			j++;
		}
		i++;
	}
}

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
					put_img_to_img(data->texture->map_img, data->texture->wall, col * IMG_SIZE, row * IMG_SIZE);
				else if (z == 1 && data->map->grid[row][col] == 1)
					put_img_to_img(data->texture->map_img, data->texture->floor, col * IMG_SIZE, row * IMG_SIZE);
				// else if (z == 2 && data->map->grid[row][col] == 'E')
					// put_img_to_img(data->texture->map_img, data->texture->exit, col * IMG_SIZE, row * IMG_SIZE);
			}
			col = -1;
		}
		row = -1;
		z++;
	}
	put_img_to_img(data->texture->map_img, data->texture->exit, data->player->y * IMG_SIZE, data->player->x * IMG_SIZE);
}

void	fill_img_color(t_img *img, int color)
{
	for (int y = 0; y < img->width; y++)
	{
		for (int x = 0; x < img->height; x++)
			img_pix_put(img, y, x, color);
	}
}

void	create_frame(t_img *img, int size, int color)
{
	for (int y = 0; y < img->width; y++)
	{
		for (int x = 0; x < img->height; x++)
		{
			if ((x < size || x >= img->height - size) || (y < size || y >= img->width - size))
				img_pix_put(img, y, x, color);
		}
	}
}

int	render(t_data *data)
{
	// (void)data;
	mlx_destroy_image(data->mlx, data->texture->base_img);
	// fill_img_color(data->texture->base_img, 0x000000);

	// img_pix_put(data->texture->img1, 32, 32, PURPLE);
	// put_img_to_img(data->texture->base_img, data->texture->img1, 0, 0);

	// mlx_put_image_to_window(data->mlx, data->mlx_win, data->texture->base_img->img_ptr, 0, 0);

	return (0);
}

void	run_game(t_data *data)
{
	mlx_init_game(data);
	printf("(run_game) hi :-) width:%d, height:%d\n", data->width, data->height);
	printf("rows:%d, cols:%d\n", data->map->row_max, data->map->col_max);
	print_grid(data->map);

	data->texture->map_img = create_img(data, NULL, data->map->col_max * IMG_SIZE, data->map->row_max * IMG_SIZE);
	data->texture->base_img = create_img(data, NULL, data->width, data->height);
	data->texture->player = create_img(data, NULL, 64, 64);
	data->texture->wall = create_img(data, NULL, 64, 64);
	fill_img_color(data->texture->wall, PURPLE);
	create_frame(data->texture->wall, 4, GREEN);
	data->texture->floor = create_img(data, NULL, 64, 64);
	fill_img_color(data->texture->floor, YELLOW);
	data->texture->exit = create_img(data, NULL, 64, 64);
	fill_img_color(data->texture->exit, GREEN);
	
	create_minimap(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->texture->map_img->img_ptr, 0, 0);
	// mlx_loop_hook(data->mlx, &render, data);
	mlx_hook(data->mlx_win, KeyPress, KeyPressMask, &handle_keypress, data);

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
