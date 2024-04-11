/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yubi42 <yubi42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:50:10 by yubi42            #+#    #+#             */
/*   Updated: 2024/04/11 14:29:45 by yubi42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	set_corners_mov(t_player *player, int sign)
{
	float	sin1;
	float	cos1;
	float	sin2;
	float	cos2;

	sin1 = sin(player->angle);
	cos1 = cos(player->angle);
	sin2 = sin(player->angle + PI / 2.0f);
	cos2 = cos(player->angle + PI / 2.0f);
	player->corners[0][0] = player->x + (IMG_SIZE / 2) + (8 * cos1) - (8 * sin1)
		+ sin1 * sign;
	player->corners[0][1] = player->y + (IMG_SIZE / 2) - (8 * sin1) - (8 * cos1)
		+ cos1 * sign;
	player->corners[1][0] = player->x + (IMG_SIZE / 2) + (8 * cos2) - (8 * sin2)
		+ sin1 * sign;
	player->corners[1][1] = player->y + (IMG_SIZE / 2) - (8 * sin2) - (8 * cos2)
		+ cos1 * sign;
	player->corners[2][0] = player->x + (IMG_SIZE / 2) + (-8 * cos1) - (-8
			* sin1) + sin1 * sign;
	player->corners[2][1] = player->y + (IMG_SIZE / 2) - (-8 * sin1) - (-8
			* cos1) + cos1 * sign;
	player->corners[3][0] = player->x + (IMG_SIZE / 2) + (-8 * cos2) - (-8
			* sin2) + sin1 * sign;
	player->corners[3][1] = player->y + (IMG_SIZE / 2) - (-8 * sin2) - (-8
			* cos2) + cos1 * sign;
}

void	set_corners_rot(t_player *player, int sign)
{
	float	sin1;
	float	cos1;
	float	sin2;
	float	cos2;

	sin1 = sin(player->angle + (0.1 * sign));
	cos1 = cos(player->angle + (0.1 * sign));
	sin2 = sin(player->angle + (0.1 * sign) + PI / 2.0f);
	cos2 = cos(player->angle + (0.1 * sign) + PI / 2.0f);
	player->corners[0][0] = (player->x + (IMG_SIZE / 2)) + (8 * cos1) - (8
			* sin1);
	player->corners[0][1] = (player->y + (IMG_SIZE / 2)) - (8 * sin1) - (8
			* cos1);
	player->corners[1][0] = (player->x + (IMG_SIZE / 2)) + (8 * cos2) - (8
			* sin2);
	player->corners[1][1] = (player->y + (IMG_SIZE / 2)) - (8 * sin2) - (8
			* cos2);
	player->corners[2][0] = (player->x + (IMG_SIZE / 2)) + (-8 * cos1) - (-8
			* sin1);
	player->corners[2][1] = (player->y + (IMG_SIZE / 2)) - (-8 * sin1) - (-8
			* cos1);
	player->corners[3][0] = (player->x + (IMG_SIZE / 2)) + (-8 * cos2) - (-8
			* sin2);
	player->corners[3][1] = (player->y + (IMG_SIZE / 2)) - (-8 * sin2) - (-8
			* cos2);
}

int	calc_mod(int num)
{
	num %= IMG_SIZE;
	if (num >= (IMG_SIZE / 2))
		num = (num - 63) * -1;
	return (num);
}

int	check_mid_wall(t_map *map, int x1, int y1, int x2, int y2, int modx,
		int mody)
{
	if (modx > mody)
	{
		// printf("check: x %i, y %i\n", x1 / IMG_SIZE, y2 / IMG_SIZE);
		if (map->grid[x1 / IMG_SIZE][y2 / IMG_SIZE] == 1)
			return (1);
	}
	else
	{
		// printf("check: x %i, y %i\n", x2 / IMG_SIZE, y1 / IMG_SIZE);
		if (map->grid[x2 / IMG_SIZE][y1 / IMG_SIZE] == 1)
			return (1);
	}
	return (0);
}

int	mid_coll(t_map *map, int x1, int y1, int x2, int y2)
{
	int	mod_x1;
	int	mod_x2;
	int	mod_y1;
	int	mod_y2;

	if (((x1 / IMG_SIZE) - (x2 / IMG_SIZE)) && ((y1 / IMG_SIZE) - (y2
				/ IMG_SIZE)))
	{
		mod_x1 = calc_mod(x1);
		mod_x2 = calc_mod(x2);
		mod_y1 = calc_mod(y1);
		mod_y2 = calc_mod(y2);
		printf("1: %i\n", mod_x1 + mod_y1);
		printf("2: %i\n", mod_x2 + mod_y2);
		if ((mod_x1 + mod_y1 <= mod_x2 + mod_y2) && check_mid_wall(map, x1, y1,
				x2, y2, mod_x1, mod_y1))
			return (1);
		else if ((mod_x2 + mod_y2 < mod_x1 + mod_y1) && check_mid_wall(map, x2,
				y2, x1, y1, mod_x2, mod_y2))
			return (1);
	}
	return (0);
}

int	calc_coll_angle(t_data *data, float *angle, char side, char dir)
{
	float	mod;
	int		num;

	mod = ((int)(data->player->angle * 1000) % (int)(0.5 * PI * 1000));
	mod /= 1000;
	if (dir == 'u')
		num = XK_Up;
	else
		num = XK_Down;
	if (side == 'l')
	{
		*angle += PI - (2 * mod);
		if (!data->player->wall_hit)
			data->rot[XK_Right] = data->rot[num];
	}
	else
	{
		*angle -= PI - (2 * mod);
		if (!data->player->wall_hit)
			data->rot[XK_Left] = data->rot[num];
	}
	if (*angle >= 2 * PI)
		*angle -= 2 * PI;
	if (*angle < 0)
		*angle += 2 * PI;
	if (!data->player->wall_hit)
		data->player->angle = *angle;
	// printf("WALL HIT\n");
	data->player->wall_hit = 1;
	data->player->dead = 1;
	return (1);
}

int	check_corner_collision(t_data *data, t_map *map, t_player *player)
{
	float	angle;

	angle = player->angle;
	if (map->grid[player->corners[0][0] / 64][player->corners[0][1] / 64] == 1)
		return (calc_coll_angle(data, &angle, 'l', 'd'));
	if (map->grid[player->corners[1][0] / 64][player->corners[1][1] / 64] == 1)
		return (calc_coll_angle(data, &angle, 'r', 'd'));
	if (map->grid[player->corners[2][0] / 64][player->corners[2][1] / 64] == 1)
		return (calc_coll_angle(data, &angle, 'l', 'u'));
	if (map->grid[player->corners[3][0] / 64][player->corners[3][1] / 64] == 1)
		return (calc_coll_angle(data, &angle, 'r', 'u'));
	if (mid_coll(map, player->corners[2][0], player->corners[2][1],
			player->corners[3][0], player->corners[3][1]) || mid_coll(map,
			player->corners[0][0], player->corners[0][1], player->corners[1][0],
			player->corners[1][1]))
	{
		data->rot[XK_Up] = MOV_MIN;
		data->rot[XK_Down] = MOV_MIN;
		player->wall_hit = 1;
		// printf("FRONT WALL HIT\n");
		player->dead = 1;
		return (1);
	}
	player->wall_hit = 0;
	return (1);
}

int	check_collision(t_data *data, int sign, char move)
{
	if (move == 'r')
		set_corners_rot(data->player, sign);
	else
		set_corners_mov(data->player, sign);
	if (check_corner_collision(data, data->map, data->player))
		return (1);
	return (0);
}
