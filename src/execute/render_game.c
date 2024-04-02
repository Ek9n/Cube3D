/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:58:23 by jborner           #+#    #+#             */
/*   Updated: 2024/04/02 17:19:04 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

// if current_x % 64 == 0 && angle < PI
// if current_x % 64 == 0 && angle >= PI
// if current_y % 64 == 0 && ( angle >= 1.5 PI || angle < 0.5 PI )
// if current_y % 64 == 0 &&  angle >= 0.5PI && angle < 1.5PI

int	wall_found(t_data *data, float current_x, float current_y)
{
	if ((int)current_x % IMG_SIZE == 0 && (int)current_y % IMG_SIZE == 0 && current_x / IMG_SIZE < data->map->row_max && current_y / IMG_SIZE < data->map->col_max)
	{
		if(data->map->grid[((int)current_x / IMG_SIZE) - 1][((int)current_y / IMG_SIZE) - 1] == 1)
			return (1);
	}
	if ((int)current_x % IMG_SIZE == 0 && current_x / IMG_SIZE < data->map->row_max && current_y / IMG_SIZE < data->map->col_max)
	{
		if(data->map->grid[(int)current_x / IMG_SIZE][(int)current_y / IMG_SIZE] == 1)
		{
			data->ray.img_dir = 'S';
			data->ray.img_col = IMG_SIZE - (int)current_y % IMG_SIZE;
			return (1);
		}
		if (data->map->grid[((int)current_x / IMG_SIZE) - 1][(int)current_y / IMG_SIZE] == 1)
		{
			data->ray.img_dir = 'N';
			data->ray.img_col = (int)current_y % IMG_SIZE;
			return (1);
		}
	}
	if((int)current_y % IMG_SIZE == 0 && current_x / IMG_SIZE < data->map->row_max && current_y / IMG_SIZE < data->map->col_max)
	{
		if (data->map->grid[(int)current_x / IMG_SIZE][(int)current_y / IMG_SIZE] == 1)
		{
			data->ray.img_dir = 'E';
			data->ray.img_col = (int)current_x % IMG_SIZE;
			return (1);
		}
		if (data->map->grid[(int)current_x / IMG_SIZE][((int)current_y / IMG_SIZE) - 1] == 1)
		{
			data->ray.img_dir = 'W';
			data->ray.img_col = IMG_SIZE - (int)current_x % IMG_SIZE;
			return (1);
		}
	}
	return (0);
}

float distance(float x1, float y1, float x2, float y2) 
{
    return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	cast_ray(t_data *data, float angle, int x, int y)
{
	float step_x;
    float step_y;
	float current_x;
    float current_y;

	current_x = x;
	current_y = y;
	step_x = sin(angle);
	step_y = cos(angle);
	data->ray.ray_len = 0;
	while (data->ray.ray_len < data->texture->minimap->base->width)
	{
		if (current_x >= IMG_SIZE && current_x < data->texture->minimap->base->height 
			&& current_y >= IMG_SIZE && current_y < data->texture->minimap->base->width)
			{
				if (wall_found(data, current_x, current_y))
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
		data->ray.ray_len += 1;
		// printf("in loop i = %f\n", data->ray.ray_len);
	}
	printf("end ray = %i\n", data->ray.ray_len);
}
// #define WALL_HEIGHT 100 // Höhe der Wand in Bildschirmpunkten
// #define VIEW_DISTANCE 200 // Maximale Betrachtungsentfernung
// // Funktion zum Rendern einer vertikalen Wand
// void render_wall(int wall_distance) {
//     // Skalieren Sie die Wandhöhe basierend auf dem Abstand des Betrachters zur Wand
//     int wall_height = WALL_HEIGHT * VIEW_DISTANCE / wall_distance;
void	generate_vertical(t_data *data, t_ray ray, int i)
{
	int	len = data->height * 20 / ray.ray_len;
	printf("len %i\n", len);
	int	j = -1;
	int	k = 0;
	int	l = 0;

	while (++j < len)
	{
		// put_pixel_img(data->texture->base_img, i * ray.ray_distance, (data->height / 2) - (len / 2) + j, GREEN);
		
		put_pixel_img(data->texture->base_img, i * ray.ray_distance, (data->height / 2) - (len / 2) + j, 
			get_pixel_img(data->texture->no, k, ray.img_col));

		k++;
		if (k % 10 == 0)
			l++;
		if (k >= IMG_SIZE)
		// if (k >= 238)
			k = 0;
		if (l == IMG_SIZE || k == 0)
			l = 0;
		// put_pixel_img(data->texture->base_img, i * ray.ray_distance, (data->height / 2) - (len / 2) + j, GREEN);
		// put_pxl_to_img_from_img(ray, data->texture->base_img, data->texture->no, 
			// i * ray.ray_distance, (data->height / 2) - (len / 2) + j);

	}
}

void	cast_rays(t_data *data, float angle, int deg, int amount) 
{
    int		start_x;
    int		start_y;
	int		i;
    float	total;
    float	step;
	float	current_angle;

	start_x = data->player->x + (data->texture->minimap->player->height / 2);
	start_y = data->player->y + (data->texture->minimap->player->width / 2);
	total = deg * (PI / 180.0);
	step = total / amount;
    current_angle = angle - (total / 2);
	// cast_ray(data, angle, start_x, start_y);
	// draw_ray_into_base(data, ray_len, i);
	data->ray.ray_amount = amount;
	data->ray.ray_distance = data->width / amount;
	printf("DISTANCE:%d\n", data->ray.ray_distance);

	i = 0;
    while (i < amount) 
	{
		// printf("1i:%d\n", i);
		// printf("1total:%f\n", total);
		// printf("1step:%f\n", step);
		// printf("1step*i:%f\n", step * i);
		// printf("1anglestep:%f\n", angle + step * i);
        // cast_ray(data, angle + step * i, start_x, start_y);
        // cast_ray(data, angle + (step * i), start_x, start_y);
        cast_ray(data, angle + (step * i) - total/2 + step/2, start_x, start_y);
		generate_vertical(data, data->ray, i);
		// if (i > 0)
		// {
		// 	cast_ray(data, angle - step * i, start_x, start_y);
		// 	generate_vertical(data, data->ray, i);
		// }

        current_angle += step;
		i++;
    }
	printf("%c\n", data->ray.img_dir);
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
	cast_rays(data, data->player->angle , 60, data->width);
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
	if (!remote_delay_ms(1))
	{
		handle_keys(data);
		render_background(data, data->texture->base_img);
		delay_reset_all(data->keys, data->delay, data->rot);
		render_minimap(data, data->texture->minimap);
		put_img_to_img(data->texture->base_img, data->texture->minimap->resize,
			10, 10);
		mlx_put_image_to_window(data->mlx, data->mlx_win,
				data->texture->base_img->img_ptr, 0, 0);
	}
	return (0);
}


//backup_canbedeleted

// void	cast_rays(t_data *data, float angle, int deg, int amount) 
// {
//     int		start_x;
//     int		start_y;
// 	int		i;
//     float	total;
//     float	step;
// 	float	current_angle;

// 	start_x = data->player->x + (data->texture->minimap->player->height / 2);
// 	start_y = data->player->y + (data->texture->minimap->player->width / 2);
// 	total = deg * (PI / 180.0);
// 	step = total / amount;
//     current_angle = angle - (total / 2);
// 	i = 0;
// 	// cast_ray(data, angle, start_x, start_y);
// 	// draw_ray_into_base(data, ray_len, i);
// 	data->ray.ray_amount = amount;
// 	data->ray.ray_distance = data->width / amount;
// 	printf("DISTANCE:%d\n", data->ray.ray_distance);

//     while (angle + (step * i) < angle + total) 
// 	{
// 		// if (i == 0)
// 		// {
//         // 	cast_ray(data, angle + step * i, start_x, start_y);
// 		// 
// 		// else if (i < amount / 2)
//         // 	cast_ray(data, angle + step * i, start_x, start_y);
// 		// else
//         // 	cast_ray(data, angle + step * i, start_x, start_y);

// 		printf("anglestep:%f\n", angle + step * i);
//         cast_ray(data, angle + step * i, start_x, start_y);
// 		generate_vertical(data, data->ray, i);
// 		// if (i > 0)
// 		// {
// 		// 	cast_ray(data, angle - step * i, start_x, start_y);
// 		// 	generate_vertical(data, data->ray, i);
// 		// }

//         current_angle += step;
// 		i++;
//     }
// 	printf("%c\n", data->ray.img_dir);
// }

// void	cast_rays(t_data *data, float angle, int deg, int amount) 
// {
//     int		start_x;
//     int		start_y;

// 	int		i;
//     float	total;
//     float	step;
// 	float	current_angle;
	
// 	start_x = data->player->x + (data->texture->minimap->player->height / 2);
// 	start_y = data->player->y + (data->texture->minimap->player->width / 2);
// 	total = deg * (2 * PI / 360.0);
// 	step = total / amount; 
//     current_angle = angle - (total / 2);  
// 	i = 0;
// 	// cast_ray(data, angle, start_x, start_y);
// 	// draw_ray_into_base(data, ray_len, i);
// 	data->ray.ray_amount = amount;
// 	data->ray.ray_distance = data->width / amount;
// 	printf("DISTANCE:%d\n", data->ray.ray_distance);

//     while (angle + (step * i) < angle + (total / 2)) 
// 	{
// 		// if (i == 0)
// 		// {
//         // 	cast_ray(data, angle + step * i, start_x, start_y);
// 		// }
// 		// else if (i < amount / 2)
//         // 	cast_ray(data, angle + step * i, start_x, start_y);
// 		// else
//         // 	cast_ray(data, angle + step * i, start_x, start_y);

//         cast_ray(data, angle + step * i, start_x, start_y);
// 		generate_vertical(data, data->ray, i);
// 		if (i > 0)
// 		{
// 			cast_ray(data, angle - step * i, start_x, start_y);
// 			generate_vertical(data, data->ray, i);
// 		}

//         current_angle += step;
// 		i++;
//     }
// 	printf("%c\n", data->ray.img_dir);
// }


// void	cast_rays(t_data *data, float angle, int deg, int amount) 
// {
//     int		start_x;
//     int		start_y;

// 	int		i;
//     float	total;
//     float	step;
// 	float	current_angle;
	
// 	start_x = data->player->x + (data->texture->minimap->player->height / 2);
// 	start_y = data->player->y + (data->texture->minimap->player->width / 2);
// 	total = deg * (2 * PI / 360.0);
// 	step = total / amount; 
//     current_angle = angle - (total / 2);  
// 	i = 0;
// 	// cast_ray(data, angle, start_x, start_y);
// 	// draw_ray_into_base(data, ray_len, i);
// 	data->ray.ray_amount = amount;
// 	data->ray.ray_distance = data->width / amount;
// 	printf("DISTANCE:%d\n", data->ray.ray_distance);

//     while (angle + (step * i) < angle + (total / 2)) 
// 	{
//         cast_ray(data, angle + step * i, start_x, start_y);
// 		generate_vertical(data, data->ray, i);
// 		// draw_ray_into_base(data, ray_len, i);
// 		if (i > 0)
// 		{
// 			cast_ray(data, angle - step * i, start_x, start_y);
// 			generate_vertical(data, data->ray, i);
// 		}
// 		// draw_ray_into_base(data, ray_len, i);

//         current_angle += step;
// 		i++;
//     }
// 	printf("%c\n", data->ray.img_dir);
// }


// void	cast_rays(t_data *data, float angle, int deg, int amount) 
// {
//     int		start_x;
//     int		start_y;

// 	int		i;
//     float	total;
//     float	step;
// 	float	current_angle;
	
// 	start_x = data->player->x + (data->texture->minimap->player->height / 2);
// 	start_y = data->player->y + (data->texture->minimap->player->width / 2);
// 	total = deg * (2 * PI / 360.0);
// 	step = total / amount; 
//     current_angle = angle - (total / 2);  
// 	i = 0;
// 	// cast_ray(data, angle, start_x, start_y);
// 	// draw_ray_into_base(data, ray_len, i);
// 	data->ray.ray_amount = amount;
// 	data->ray.ray_distance = data->width / amount;
// 	printf("DISTANCE:%d\n", data->ray.ray_distance);

//     while (angle + (step * i) < angle + (total / 2)) 
// 	{
// 		if (i == 0)
//         	cast_ray(data, angle + step * i, start_x, start_y);
// 		else if (i < amount/2)
//         	cast_ray(data, angle + step * -i, start_x, start_y);
// 		else
//         	cast_ray(data, angle + step * i, start_x, start_y);
// 		// generate_vertical(data, data->ray, i);
// 		// draw_ray_into_base(data, ray_len, i);
	
// 		// if (i > 0)
// 		// {
// 		// 	cast_ray(data, angle - step * i, start_x, start_y);
// 		// 	generate_vertical(data, data->ray, i);
// 		// }

// 		// draw_ray_into_base(data, ray_len, i);

//         current_angle += step;
// 		i++;
//     }
// 	printf("%c\n", data->ray.img_dir);
// }

