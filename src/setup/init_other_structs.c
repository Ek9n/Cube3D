/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_other_structs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:46:24 by yubi42            #+#    #+#             */
/*   Updated: 2024/06/02 01:01:01 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	init_setup_vars(t_texture_ok *setup_vars)
{
	setup_vars->no = FALSE;
	setup_vars->so = FALSE;
	setup_vars->ea = FALSE;
	setup_vars->we = FALSE;
	setup_vars->f = FALSE;
	setup_vars->c = FALSE;
}

void	init_reading(t_read *reading)
{
	reading->return_value = TRUE;
	reading->str = NULL;
	reading->i = 0;
}

void	init_minimap(t_minimap *minimap)
{
	minimap->base = NULL;
	minimap->resize = NULL;
	minimap->small = NULL;
	minimap->wall = NULL;
	minimap->ground = NULL;
	minimap->player = NULL;
	minimap->player_rot = NULL;
}

void	init_3d_textures(t_texture *texture)
{
	texture->num0 = NULL;
	texture->num1 = NULL;
	texture->num2 = NULL;
	texture->num3 = NULL;
	texture->num4 = NULL;
	texture->num5 = NULL;
	texture->num6 = NULL;
	texture->num7 = NULL;
	texture->num8 = NULL;
	texture->num9 = NULL;
	texture->slash = NULL;
	texture->kmh = NULL;
	texture->game_over = NULL;
	texture->high_score = NULL;
	texture->your_score = NULL;
	texture->steeringwheel = NULL;
	texture->steeringwheel2 = NULL;
	texture->carframe = NULL;
	texture->carframe2 = NULL;
	texture->goal = NULL;
	texture->no = NULL;
	texture->so = NULL;
	texture->ea = NULL;
	texture->we = NULL;
}

void	init_texture(t_texture *texture)
{
	texture->sprite1 = NULL;
	init_3d_textures(texture);
	texture->minimap = NULL;
	texture->no_path = NULL;
	texture->so_path = NULL;
	texture->we_path = NULL;
	texture->ea_path = NULL;
	texture->base_img = NULL;
	texture->base_img2 = NULL;
	texture->base_img2_resize = NULL;
	texture->alpha = NULL;
	texture->alpha2 = NULL;
	texture->img1 = NULL;
	texture->img2 = NULL;
	texture->black = NULL;
	texture->transparent = NULL;
	texture->f[0] = -1;
	texture->f[1] = -1;
	texture->f[2] = -1;
	texture->c[0] = -1;
	texture->c[1] = -1;
	texture->c[2] = -1;
	texture->map_str = NULL;
}
