/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jborner <jborner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:29:02 by hstein            #+#    #+#             */
/*   Updated: 2024/04/15 16:36:36 by jborner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	calc_speed(t_data *data, int sign)
{
	if (sign < 0)
		data->player->speed[1] = sqrt((data->player->dx * data->player->dx)
			+ (data->player->dy * data->player->dy));
	else
		data->player->speed[2] = sqrt((data->player->dx * data->player->dx)
			+ (data->player->dy * data->player->dy));
	if (data->rot[XK_Up] <= MOV_MIN)
		data->player->speed[2] = 0;
	if (data->rot[XK_Down] <= MOV_MIN)
		data->player->speed[1] = 0;
	data->player->speed[0] = (data->player->speed[2] - data->player->speed[1])
		* 10;
	if (data->player->speed[0] < 0)
		data->player->speed[0] *= -1;
}

void	move_player(t_data *data, int sign, int num, int other_num)
{
	data->delay[num] %= ANIM_DELAY;
	data->delay[num] += 1;
	if (data->delay[num] != 1)
		return ;
	if (!data->player->dead && (data->keys[num] || data->keys[other_num]) && data->rot[num] < 55)
		data->rot[num] += 1;
	else 
		data->rot[num] -= 1;
	if (data->rot[num] > MOV_MIN)
	{
	data->player->dx = sin(data->player->angle) * (1 + (((data->rot[num]
					* data->rot[num])) / 200));
	data->player->dy = cos(data->player->angle) * (1 + (((data->rot[num]
					* data->rot[num])) / 200));
	data->player->x += data->player->dx * sign;
	data->player->y += data->player->dy * sign;
	}
	calc_speed(data, sign);
	// printf("cur speed: %i km/h\n", (int)data->player->speed[0]);
}

void	rotate_player(t_data *data, int sign, int num, int *delay)
{
	printf("num: %i\n", num);
	*delay %= ANIM_DELAY;
	*delay += 1;
	if (*delay != 1)
		return ;
	// printf("rot_dir %f, num %i\n", data->rot_dir, num);
	printf("test: rot_dir: %f\n", data->rot_dir);
	if (!data->player->dead &&  data->keys[num] && data->rot_dir * sign < 0.005)
	{
		data->rot_dir += 0.0002 * sign;
		printf("keypress: rot_dir: %f\n", data->rot_dir);
	}
	else if (data->rot_dir * sign >  0.0000 && !data->keys[num])
	{
		data->rot_dir -= 0.0001 * sign;
		printf("not pressed rot_dir: %f\n", data->rot_dir);
		if (data->rot_dir == 0.0001 * sign)
			data->rot_dir = 0;
	}
		
	if (data->rot_dir * sign >  0.000000)
	{
	data->player->angle += 0.1 * (1 + 0.001 * (((data->rot_dir)
					 * (data->rot_dir)))) * sign;
	adjust_angle(&data->player->angle);
	data->player->x_sin = sin(data->player->angle);
	data->player->y_cos = cos(data->player->angle);
	}
}

void move_side(t_data *data, int sign, int num)
{
	data->delay[num] %= ANIM_DELAY;
	data->delay[num] += 1;
	if (data->delay[num] != 1)
		return ;
	data->player->x += sin(data->player->angle + (0.5 * PI * sign)) * SIDESTEP;
	data->player->y += cos(data->player->angle + (0.5 * PI * sign)) * SIDESTEP;
}

void	handle_keys(t_data *data)
{
	if (data->keys[XK_Escape])
		close_game(data, NULL);
	if (data->rot[XK_Right] || ((data->rot_dir > 0) /* && !data->keys[XK_Left] */))
		rotate_player(data, 1, XK_Right, &data->delay[XK_Right]);
	if (data->rot[XK_Left] || ((data->rot_dir < 0) /* && !data->keys[XK_Right] */))
		rotate_player(data, -1, XK_Left, &data->delay[XK_Right]);
	if ((data->keys[XK_Up] || data->keys[XK_w] || data->rot[XK_Up] > MOV_MIN))
		move_player(data, 1, XK_Up, XK_w);
	if ((data->keys[XK_Down] || data->keys[XK_s]
			|| data->rot[XK_Down] > MOV_MIN))
		move_player(data, -1, XK_Down, XK_s);
	if (data->keys[XK_a])
		move_side(data, -1, XK_a);
	if (data->keys[XK_d])
		move_side(data, 1, XK_d);
	check_collision(data);
	
}

int	handle_keypress(int keysym, t_data *data)
{
	if(!data->player->dead || keysym == XK_Escape)
		data->keys[keysym] = 1;
	return (0);
}

int	handle_keyrelease(int keysym, t_data *data)
{
	data->keys[keysym] = 0;
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
