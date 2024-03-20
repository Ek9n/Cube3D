/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yubi42 <yubi42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:58:23 by jborner           #+#    #+#             */
/*   Updated: 2024/03/20 07:22:44 by yubi42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	render_minimap(t_data *data, t_minimap *minimap)
{
	int	col;
	int	row;

	row = -1;
	while (++row < data->map->row_max)
	{
		col = -1;
		while (++col < data->map->col_max)
		{
			if (data->map->grid[row][col] == 0)
				put_img_to_img(minimap->base, minimap->ground, col
					*IMG_SIZE, row * IMG_SIZE);
			else if (data->map->grid[row][col] == 1)
				put_img_to_img(minimap->base, minimap->wall, col
					*IMG_SIZE, row * IMG_SIZE);
		}
	}
	rotate_img(data, &minimap->player, &minimap->player_rot);
	put_img_to_img(minimap->base, minimap->player_rot, data->player->y, data->player->x);
	copy_to_small(data->player->x, data->player->y, minimap->base, minimap->small);
	if(minimap->resize)
		free_img(minimap->resize, data->mlx);
	minimap->resize = resize_img(data, &minimap->small, data->width / minimap->resize_value, data->width / minimap->resize_value);
	create_frame(minimap->resize, 5, BLACK);
}

void	render_background(t_data *data, t_image *bg)
{
int x;
int y;

x = 0;
while (x < bg->height)
{
	y = 0;
	while (y < bg->width)
	{
		if (x < (bg->height / 2))
			img_pix_put(bg, y, x, rgb_to_hex(data->texture->c));
		else
			img_pix_put(bg, y, x, rgb_to_hex(data->texture->f));
		++y;
	}
	++x;
}
}



int		render(t_data *data)
{
	render_background(data, data->texture->base_img);
	render_minimap(data, data->texture->minimap);
	put_img_to_img(data->texture->base_img, data->texture->minimap->resize, 10, 10);
	mlx_put_image_to_window(data->mlx, data->mlx_win,
		data->texture->base_img->img_ptr, 0, 0);
	return(0);
}