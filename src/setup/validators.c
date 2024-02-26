/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yubi42 <yubi42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:58:15 by yubi42            #+#    #+#             */
/*   Updated: 2024/02/26 15:37:12 by yubi42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	map_validator(t_data *data, t_cub cub, char (*err)[50])
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (malloc_err(map, NULL, err))
		return (FALSE);
	init_map(map);
	data->map = map;
	count_map_row_col(cub.map_str, &map->col_max, &map->row_max);
	create_grid(map);
	if (malloc_err(&map->grid, NULL, err))
		return (FALSE);
	if (!fill_grid(cub.map_str, map, err) || !check_grid(map, err))
		return (FALSE);
	return (TRUE);
}

int	file_validator(char *file, t_cub *cub, char (*err)[50])
{
	t_read		reading;
	t_cub_ok	setup_vars;

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