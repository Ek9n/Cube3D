/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yubi42 <yubi42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:50:10 by yubi42            #+#    #+#             */
/*   Updated: 2024/04/30 14:52:56 by yubi42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	set_corners(t_player *player)
{
	double	sin1;
	double	cos1;
	double	sin2;
	double	cos2;

	sin1 = sin(player->angle);
	cos1 = cos(player->angle);
	sin2 = sin(player->angle + PI / 2.0f);
	cos2 = cos(player->angle + PI / 2.0f);
	player->corners[0][0] = player->x + (IMG_SIZE / 2) + (8 * cos1) - (8
			* sin1);
	player->corners[0][1] = player->y + (IMG_SIZE / 2) - (8 * sin1) - (8
			* cos1);
	player->corners[1][0] = player->x + (IMG_SIZE / 2) + (8 * cos2) - (8
			* sin2);
	player->corners[1][1] = player->y + (IMG_SIZE / 2) - (8 * sin2) - (8
			* cos2);
	player->corners[2][0] = player->x + (IMG_SIZE / 2) + (-8 * cos1) - (-8
			* sin1);
	player->corners[2][1] = player->y + (IMG_SIZE / 2) - (-8 * sin1) - (-8
			* cos1);
	player->corners[3][0] = player->x + (IMG_SIZE / 2) + (-8 * cos2) - (-8
			* sin2);
	player->corners[3][1] = player->y + (IMG_SIZE / 2) - (-8 * sin2) - (-8
			* cos2);
}

int	mid_coll(t_map *map, int corner1[2], int corner2[2])
{
	int	mod_corner1[2];
	int	mod_corner2[2];

	if (((corner1[0] / IMG_SIZE) - (corner2[0] / IMG_SIZE)) && ((corner1[1]
				/ IMG_SIZE) - (corner2[1] / IMG_SIZE)))
	{
		mod_corner1[0] = calc_mod(corner1[0]);
		mod_corner2[0] = calc_mod(corner2[0]);
		mod_corner1[1] = calc_mod(corner1[1]);
		mod_corner2[1] = calc_mod(corner2[1]);
		if ((mod_corner1[0] + mod_corner1[1] <= mod_corner2[0] + mod_corner2[1])
			&& check_mid_wall(map, corner1, corner2, mod_corner1))
			return (1);
		else if ((mod_corner2[0] + mod_corner2[1] < mod_corner1[0]
				+ mod_corner1[1]) && check_mid_wall(map, corner2, corner1,
				mod_corner2))
			return (1);
	}
	return (0);
}

int	is_wall(t_map *map, int x, int y)
{
	if (map->grid[x / IMG_SIZE][y / IMG_SIZE] == 1)
		return (1);
	return (0);
}

int	check_corner_collision(t_data *data, t_map *map, t_player *player)
{
	double	angle;

	angle = player->angle;
	if (is_wall(map, player->corners[0][0], player->corners[0][1]))
		return (calc_coll_angle(data, &angle, XK_Left, XK_Down));
	if (is_wall(map, player->corners[1][0], player->corners[1][1]))
		return (calc_coll_angle(data, &angle, XK_Right, XK_Down));
	if (is_wall(map, player->corners[2][0], player->corners[2][1]))
		return (calc_coll_angle(data, &angle, XK_Right, XK_Up));
	if (is_wall(map, player->corners[3][0], player->corners[3][1]))
		return (calc_coll_angle(data, &angle, XK_Left, XK_Up));
	if (mid_coll(map, player->corners[2], player->corners[3]) || mid_coll(map,
			player->corners[0], player->corners[1]))
	{
		data->rot[XK_Up] = MOV_MIN;
		data->rot[XK_Down] = MOV_MIN;
		player->wall_hit = 1;
		player->dead = 1;
		return (1);
	}
	player->wall_hit = 0;
	return (1);
}

void	check_collision(t_data *data)
{
	set_corners(data->player);
	if (in_border(data))
		check_corner_collision(data, data->map, data->player);
}
