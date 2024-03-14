/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:29:02 by hstein            #+#    #+#             */
/*   Updated: 2024/03/14 18:04:10 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"


int	collision(t_data *data)
{
	int	col;
	int	row;

	// x = -1;
	// y = -1;
	// while (++x < data->map->row_max)
	// {
	// 	while (++y < data->map->col_max)
	// 	{
	// 		if (data->map->grid[y][x] == data->player->x >= data->map->grid[y][x])
	// 	}
	// 	y = -1;
	// }
	printf("player->y: %f, player->x: %f\n", data->player->y, data->player->x);
	// int	mod = data->player->x % IMG_SIZE;
	col = data->player->y / IMG_SIZE;
	row = data->player->x / IMG_SIZE;
	printf("col: %d, row %d\n", col, row);
	printf("data->map->grid[row][col]: %d\n", data->map->grid[row][col]);
	if (data->map->grid[row][col] == 1)
		return (1);
	// if (mod != 0 && data->map->grid[row][col])
	// if (data->map->grid[data->player->y][data->player->x] == 1)
	// 	return (1);
	return (0);
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Up)
		data->player->x -= 4;
	if (keysym == XK_Down)
		data->player->x += 4;
	if (keysym == XK_Left)
		data->player->y -= 4;
	if (keysym == XK_Right)
	{
		data->player->y += 4;
		if (collision(data))
			data->player->y -= 4;
	}
	if (keysym == XK_Escape)
		close_game(data, NULL);
	return (0);
}

// int	handle_mouse(int button, int x, int y, t_data *data)
// {
// 	(void)x;
// 	(void)y;
// 	if (button == 1)
// 	{
// 		data->map.translate_active = !data->map.translate_active;
// 		mlx_mouse_get_pos(data->mlx_ptr, data->win_ptr,
// 			&data->mouse_x, &data->mouse_y);
// 	}
// 	return (0);
// }
