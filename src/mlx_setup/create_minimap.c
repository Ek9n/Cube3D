/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yubi42 <yubi42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:04:35 by jborner           #+#    #+#             */
/*   Updated: 2024/03/15 15:09:49 by yubi42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"


void	create_minimap_texture(t_minimap *minimap, t_data *data)
{
	minimap->base = create_img(data, NULL, IMG_SIZE * data->map->col_max, IMG_SIZE * data->map->col_max);
	data->texture->minimap->small = create_img(data, NULL, 5 * IMG_SIZE, 5 * IMG_SIZE);
	minimap->ground = create_img(data, NULL , 64, 64);
	fill_img_color(minimap->ground, BLUE);
	create_frame(minimap->ground, 1, BLACK);
	minimap->wall = create_img(data, NULL, 64, 64);
	fill_img_color(minimap->wall, PURPLE);
	create_frame(minimap->wall, 1, BLACK);
	minimap->player = create_img(data, NULL , 64, 64);
	fill_img_color(minimap->player, RED);
	create_frame(minimap->player, 24, TRANS);
	minimap->exit = create_img(data, NULL, 64, 64);
	fill_img_color(minimap->exit, GREEN);
}

void copy_to_small(int player_row, int player_col, t_image *full, t_image *part)
{
	int start_row;
	int start_col;
	int x;
	int y;
	int color;

	start_row = player_row - (2 * IMG_SIZE);
	start_col = player_col - (2 * IMG_SIZE);
	y = 0;
	while (y < part->height)
	{
        x = 0;
		while (x < part->width)
		{
			put_pixel_img(part, x, y, 000001);
			if ((x + start_col >= 0 && x + start_col < full->width) && (y + start_row >= 0 && y + start_row < full->height))
			{
			color = get_pixel_img(full, x + start_col, y + start_row);
			put_pixel_img(part, x, y, color);
			}
            x++;
		}
        y++;
	}
}


void	create_minimap(t_data *data)
{
	data->texture->minimap = malloc(sizeof(t_minimap));
	if(!data->texture->minimap)
		close_game(data, "Unable to allocate memory");
	init_minimap(data->texture->minimap);
	data->texture->minimap->resize_value = 5;
	create_minimap_texture(data->texture->minimap, data);
}