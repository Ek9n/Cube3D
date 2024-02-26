/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yubi42 <yubi42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:46:24 by yubi42            #+#    #+#             */
/*   Updated: 2024/02/26 15:37:24 by yubi42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	init_setup_vars(t_cub_ok *setup_vars)
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

void	init_cub(t_cub *cub)
{
	cub->no = NULL;
	cub->so = NULL;
	cub->we = NULL;
	cub->ea = NULL;
	cub->f[0] = -1;
	cub->f[1] = -1;
	cub->f[2] = -1;
	cub->c[0] = -1;
	cub->c[1] = -1;
	cub->c[2] = -1;
	cub->map_str = NULL;
}

void	init_map(t_map *map)
{
	map->grid = NULL;
	map->col_max = 0;
	map->row_max = 0;
	map->i = 0;
	map->j = 0;
}

void	init_data(t_data *data)
{
	data->err[0] = '\0';
	data->map = NULL;
}
