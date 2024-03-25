/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jborner <jborner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:58:23 by jborner           #+#    #+#             */
/*   Updated: 2024/03/25 15:15:42 by jborner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

// if current_x % 64 == 0 && angle < PI
// if current_x % 64 == 0 && angle >= PI
// if current_y % 64 == 0 && ( angle >= 1.5 PI || angle < 0.5 PI )
// if current_y % 64 == 0 &&  angle >= 0.5PI && angle < 1.5PI

int		wall_found(t_data *data, float current_x, float current_y, float angle)
{
	if ((int)current_x % IMG_SIZE == 0 && (int)current_y % IMG_SIZE == 0 && current_x / IMG_SIZE < data->map->row_max && current_y / IMG_SIZE < data->map->col_max)
	{
		if(data->map->grid[((int)current_x / IMG_SIZE) - 1][((int)current_y / IMG_SIZE) - 1] == 1)
			return (1);
	}
	if ((int)current_x % IMG_SIZE == 0 && current_x / IMG_SIZE < data->map->row_max && current_y / IMG_SIZE < data->map->col_max)
	{
		if(angle < PI && data->map->grid[(int)current_x / IMG_SIZE][(int)current_y / IMG_SIZE] == 1)
			return (1);
		if (angle >= PI && data->map->grid[((int)current_x / IMG_SIZE) - 1][(int)current_y / IMG_SIZE] == 1)
			return (1);
	}
	if((int)current_y % IMG_SIZE == 0 && current_x / IMG_SIZE < data->map->row_max && current_y / IMG_SIZE < data->map->col_max)
	{
		if (((angle >= 1.5 * PI || angle < 0.5 * PI)) && data->map->grid[(int)current_x / IMG_SIZE][(int)current_y / IMG_SIZE] == 1)
			return (1);
		if ((angle >= 0.5 * PI && angle < 1.5 *PI) && data->map->grid[(int)current_x / IMG_SIZE][((int)current_y / IMG_SIZE) - 1] == 1)
			return (1);
	}
	
	return (0);
}

float distance(float x1, float y1, float x2, float y2) 
{
    return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	cast_ray(t_data *data, float angle, int x, int y)
{
	int	ray_len;
	float step_x;
    float step_y;
	float current_x;
    float current_y;

	current_x = x;
	current_y = y;
	step_x = sin(angle);
	step_y = cos(angle);
	ray_len = 0;
	while (ray_len < data->texture->minimap->base->width)
	{
		if (current_x >= IMG_SIZE && current_x < data->texture->minimap->base->height 
			&& current_y >= IMG_SIZE && current_y < data->texture->minimap->base->width)
			{
				if(wall_found(data, current_x, current_y, angle))
				{
					// distance(x,y, current_x,current_y);
					break;
				}
				put_pixel_img(data->texture->minimap->base, (int)current_y, (int)current_x, GREEN);
			}
			
		else
			break ;
		current_x += step_x;
        current_y += step_y;
		ray_len += 1;
		// printf("in loop i = %f\n", ray_len);
	}
	printf("end ray = %i\n", ray_len);
}

void cast_rays(t_data *data, float angle/* , int deg, int amount */) 
{
    int start_x;
    int start_y;

/* 	int i;
    float total;
    float step;
	float current_angle; */
	
	start_x = data->player->x + (data->texture->minimap->player->height / 2) +1;
	start_y = data->player->y + (data->texture->minimap->player->width / 2) +1;
/* 	total = deg * (2 * PI / 360.0);
	step = total / (amount); 
    current_angle = angle - (total / 2);  
	i = 0; */
	cast_ray(data, angle, start_x, start_y);
	// draw_ray_into_base(data, ray_len, i);
/* 
    while (angle + (step * i) < angle + (total / 2)) 
	{
        cast_ray(data, angle + step * i, start_x, start_y);
		// draw_ray_into_base(data, ray_len, i);
		cast_ray(data, angle - step * i, start_x, start_y);
		// draw_ray_into_base(data, ray_len, i);
        current_angle += step;
		i++;
    } */
}

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
				put_img_to_img(minimap->base, minimap->ground, col * IMG_SIZE,
					row * IMG_SIZE);
			else if (data->map->grid[row][col] == 1)
				put_img_to_img(minimap->base, minimap->wall, col * IMG_SIZE, row
					* IMG_SIZE);
		}
	}
	rotate_img(data, &minimap->player, &minimap->player_rot);
	put_img_to_img(minimap->base, minimap->player_rot, data->player->y,
		data->player->x);
	cast_rays(data, data->player->angle /* , 60, 30 */);
	copy_to_small(data->player->x, data->player->y, minimap->base,
		minimap->small);
	if (minimap->resize)
		free_img(minimap->resize, data->mlx);
	minimap->resize = resize_img(data, &minimap->small, data->width
		/ minimap->resize_value, data->width / minimap->resize_value);
	create_frame(minimap->resize, 5, BLACK);
}

void	render_background(t_data *data, t_image *bg)
{
	int	x;
	int	y;

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

void	delay_reset_one(int *delay, int *rot)
{
	*delay = 0;
	*rot = ROT_MIN;
}

void	delay_reset_all(int *key, int *delay, int *rot)
{
	if (delay[XK_Right] != 0 && (key[XK_Right] == 0 && key[XK_d] == 0)
		&& rot[XK_Right] <= ROT_MIN)
		delay_reset_one(&delay[XK_Right], &rot[XK_Right]);
	if (delay[XK_Left] != 0 && (key[XK_Left] == 0 && key[XK_a] == 0)
		&& rot[XK_Left] <= ROT_MIN)
		delay_reset_one(&delay[XK_Left], &rot[XK_Left]);
	if (delay[XK_Up] != 0 && (key[XK_Up] == 0 && key[XK_w] == 0)
		&& rot[XK_Up] <= ROT_MIN)
		delay_reset_one(&delay[XK_Up], &rot[XK_Up]);
	if (delay[XK_Down] != 0 && (key[XK_Down] == 0 && key[XK_s] == 0)
		&& rot[XK_Down] <= ROT_MIN)
		delay_reset_one(&delay[XK_Down], &rot[XK_Down]);
}

/* int	new_render_req(t_data *data)
{
	if (data->keys[XK_Right] || data->keys[XK_d]
		|| data->rot[XK_Right] > ROT_MIN || data->keys[XK_Left]
		|| data->keys[XK_a] || data->rot[XK_Left] > ROT_MIN || data->keys[XK_Up]
		|| data->keys[XK_w] || data->rot[XK_Up] > ROT_MIN || data->keys[XK_Down]
		|| data->keys[XK_s] || data->rot[XK_Down] > ROT_MIN)
		return (1);
	return (0);
}
 */

int	render(t_data *data)
{
	int i;
	i = 0;
	while (i < 10000)
		i++;
	handle_keys(data);
	render_background(data, data->texture->base_img);
	delay_reset_all(data->keys, data->delay, data->rot);
	render_minimap(data, data->texture->minimap);
	put_img_to_img(data->texture->base_img, data->texture->minimap->resize,
		10, 10);
	mlx_put_image_to_window(data->mlx, data->mlx_win,
			data->texture->base_img->img_ptr, 0, 0);
	return (0);
}