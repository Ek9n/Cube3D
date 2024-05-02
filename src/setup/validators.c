/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jborner <jborner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:58:15 by yubi42            #+#    #+#             */
/*   Updated: 2024/05/02 15:37:14 by jborner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	opt1_fill_start(t_map *map, int k, int opt)
{
	while ((map->grid[k][map->i] != 1 && map->grid[k][map->i] != -1)
		&& (k < map->row_max && k >= 0) && (map->i < map->col_max
			&& map->i >= 0))
	{
		map->grid[k][map->i] = 2;
		if (opt == 1)
			++k;
		else
			--k;
	}
}

void	opt2_fill_start(t_map *map, int k, int opt)
{
	while ((map->grid[map->j][k] != 1 && map->grid[map->j][k] != -1)
		&& (k < map->col_max && k >= 0) && (map->j < map->row_max
			&& map->j >= 0))
	{
		map->grid[map->j][k] = 2;
		if (opt == 1)
			++k;
		else
			--k;
	}
}

void	choose_fill_start(t_map *map, int c)
{
	map->grid[map->j][map->i] = 0;
	if (c == 2)
	{
		map->j -= 1;
		opt2_fill_start(map, map->i, 1);
		opt2_fill_start(map, map->i, 2);
	}
	else if (c == 3)
	{
		map->i += 1;
		opt1_fill_start(map, map->j, 1);
		opt1_fill_start(map, map->j, 2);
	}
	else if (c == 4)
	{
		map->j += 1;
		opt2_fill_start(map, map->i, 1);
		opt2_fill_start(map, map->i, 2);
	}
	else if (c == 5)
	{
		map->i -= 1;
		opt1_fill_start(map, map->j, 1);
		opt1_fill_start(map, map->j, 2);
	}
}

void	set_start(t_map *map)
{
	while (map->j < map->row_max)
	{
		map->i = -1;
		while (map->i < map->col_max - 1)
		{
			map->i++;
			if (map->grid[map->j][map->i] == 2 || map->grid[map->j][map->i] == 3
				|| map->grid[map->j][map->i] == 4
				|| map->grid[map->j][map->i] == 5)
			{
				choose_fill_start(map, map->grid[map->j][map->i]);
				break ;
			}
		}
		if (map->grid[map->j][map->i] == 2 || map->grid[map->j][map->i] == 3
			|| map->grid[map->j][map->i] == 4 || map->grid[map->j][map->i] == 5)
			break ;
		map->j++;
	}
}

int	map_validator(t_data *data, t_texture cub, char (*err)[50])
{
	count_map_row_col(cub.map_str, &data->map->col_max, &data->map->row_max);
	create_grid(data->map);
	if (malloc_err(&data->map->grid, NULL, err))
		return (FALSE);
	if (!fill_grid(cub.map_str, data->map, data->player, err))
		return (FALSE);
	data->map->i = 0;
	data->map->j = 0;
	if (!check_grid(data->map, err))
		return (FALSE);
	data->map->i = 0;
	data->map->j = 0;
	set_start(data->map);
	return (TRUE);
}

int	file_validator(char *file, t_texture *cub, char (*err)[50])
{
	t_read			reading;
	t_texture_ok	setup_vars;

	init_setup_vars(&setup_vars);
	init_reading(&reading);
	reading.fd = open(file, O_RDONLY);
	if (reading.fd < 0)
		return (FALSE);
	reading.bytes = read(reading.fd, &reading.buf, 1);
	setup_vars_check(cub, &reading, &setup_vars, err);
	if (reading.str)
		free(reading.str);
	reading.str = NULL;
	if (setup_found(setup_vars) && reading.return_value == TRUE)
		setup_map_str(cub, &reading, err);
	close(reading.fd);
	return (reading.return_value);
}

int	input_validator(int ac, char **av, char (*err)[50])
{
	ft_strlcpy(*err, "Incorrect input",
			ft_strlen("Incorrect input") + 1);
	if (ac != 2)
	{
		ft_strlcpy(*err, "Usage: ./cube3d *.cub",
			ft_strlen("Usage: ./cube3d *.cub") + 1);
		return (FALSE);
	}
	if (ft_strncmp(&av[1][ft_strlen(av[1]) - ft_strlen(".cub")], ".cub",
			5) != 0)
	{
		ft_strlcpy(*err, "Usage: ./cube3d *.cub",
			ft_strlen("Usage: ./cube3d *.cub") + 1);
		return (FALSE);
	}
	return (TRUE);
}
