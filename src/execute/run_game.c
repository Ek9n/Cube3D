/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:41:09 by hstein            #+#    #+#             */
/*   Updated: 2024/03/18 20:15:20 by hstein           ###   ########.fr       */
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

void	rot_pxl(t_img *img)
{
	// int x;
	// int y;

	// double scale;

	// scale = 1;
	// x = 0;

	// printf("img->height = %d\n", img->height);
	float	rot = 30.0 / 180.0 * PI;
	// int off_x = 25;
	// int off_y = 0;

	while (x < img->height)
	{
		y = 0;
		while (y < img->width)
		{
			// z = map->coords[x][y].z;

			//printf("off_x: %f, off_y: %f\n", off_x, off_y);
			map->a_z = 30.0 / 180 * 3.145;
			map->a_x = 30.0 / 180 * 3.145;

			float cos_z = cos(map->a_z);
			float sin_z = sin(map->a_z);
			// float cos_x = cos(map->a_x);
			// float sin_x = sin(map->a_x);

			// map->coords[x][y].x_iso = x * cos(map->a_z) - y * sin(map->a_z);
			// map->coords[x][y].y_iso = (x * sin(map->a_z) + y * cos(map->a_z)) * cos(map->a_x) + z * sin(map->a_x);
			
			double xx;
			double yy;
			xx = x * cos_z - y * sin_z;
			yy = x * sin_z + y * cos_z;
			// xx = (x - off_x) * cos_z - (y - off_y) * sin_z;
			// yy = (x - off_x) * sin_z + (y - off_y) * cos_z;

			// rotate around x-axis:
			// yy = yy * cos_x - z * sin_x;

			// z = yy * sin_x + z * cos_x;
			printf("xx=%f yy=%f\n", xx, yy);
			printf("off_xx=%f off_yy=%f\n", off_x, off_y);

			// xx = x;
			// yy = y;
			if (xx + off_x <= HEIGHT && xx + off_x >= 0 && yy + off_y <= WIDTH && yy + off_y >= 0)
			{
				// img_pix_put(&data->img, yy, xx, GREEN_PIXEL);
				img_pix_put(&data->img, yy + off_y, xx + off_x, GREEN_PIXEL);
				// img_pix_put(&data->img, yy + off_y + 50, xx + off_x, GREEN_PIXEL);

			}

			// map->coords[x][y].x = xx * scale;
			// map->coords[x][y].y = yy * scale;
			// printf("z=%d x=%f y=%f\n", z, map->coords[(int)x][(int)y].x_iso, map->coords[(int)x][(int)y].y_iso);
			y++;
		}
		x++;
	}
}

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
					put_img_to_img(data->texture->map_img, data->texture->floor, col * IMG_SIZE, row * IMG_SIZE);
				else if (z == 1 && data->map->grid[row][col] == 1)
					put_img_to_img(data->texture->map_img, data->texture->wall, col * IMG_SIZE, row * IMG_SIZE);
				// else if (z == 2 && data->map->grid[row][col] == 'E')
					// put_img_to_img(data->texture->map_img, data->texture->exit, col * IMG_SIZE, row * IMG_SIZE);
			}
			col = -1;
		}
		row = -1;
		z++;
	}
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
	// mlx_destroy_image(data->mlx, data->texture->map_img);
	// fill_img_color(data->texture->base_img, 0x000000);

	// mlx_put_image_to_window(data->mlx, data->mlx_win, data->texture->map_img->img_ptr, 0, 0);
	put_img_to_img(data->texture->base_img, data->texture->map_img, 0, 0);
	rot_pxl(data->texture->player);
	put_img_to_img(data->texture->base_img, data->texture->player, data->player->y, data->player->x);
	// put_img_to_img(data->texture->base_img, data->texture->player, data->player->y * IMG_SIZE, data->player->x * IMG_SIZE);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->texture->base_img->img_ptr, 0, 0);

	return (0);
}

void	run_game(t_data *data)
{
	mlx_init_game(data);
	printf("(run_game) hi :-) width:%d, height:%d\n", data->width, data->height);
	printf("rows:%d, cols:%d\n", data->map->row_max, data->map->col_max);
	print_grid(data->map);

	data->texture->base_img = create_img(data, NULL, data->width, data->height);

	data->texture->map_img = create_img(data, NULL, data->map->col_max * IMG_SIZE, data->map->row_max * IMG_SIZE);
	create_frame(data->texture->map_img, 10, 0xFFFFFF);

	data->texture->player = create_img(data, NULL, 64, 64);
	fill_img_color(data->texture->player, GREEN);
	create_frame(data->texture->player, 24, TRANS);

	data->texture->floor = create_img(data, NULL, 64, 64);
	fill_img_color(data->texture->floor, BLUE);
	create_frame(data->texture->floor, 1, BLACK);

	data->texture->wall = create_img(data, NULL, 64, 64);
	fill_img_color(data->texture->wall, PURPLE);
	create_frame(data->texture->wall, 1, BLACK);

	data->texture->exit = create_img(data, NULL, 64, 64);
	fill_img_color(data->texture->exit, GREEN);

	create_minimap(data);
	// mlx_put_image_to_window(data->mlx, data->mlx_win, data->texture->map_img->img_ptr, 0, 0);

	mlx_loop_hook(data->mlx, &render, data);
	mlx_hook(data->mlx_win, KeyPress, KeyPressMask, &handle_keypress, data);
	// mlx_key_hook (void *win_ptr, int (*funct_ptr)(), void *param);
	// mlx_expose_hook (void *win_ptr, int (*funct_ptr)(), void *param);

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
