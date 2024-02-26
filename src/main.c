/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yubi42 <yubi42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 15:47:45 by yubi42            #+#    #+#             */
/*   Updated: 2024/02/26 14:16:13 by yubi42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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

int	malloc_err(void *ptr, int *return_value, char (*err)[50])
{
	if (!ptr)
	{
		ft_strlcpy(*err, "Not enough memory", ft_strlen("Not enough memory")
			+ 1);
		if (return_value != NULL)
			*return_value = FALSE;
		return (TRUE);
	}
	return (FALSE);
}

void	init_setup_vars(t_cub_ok *setup_vars)
{
	setup_vars->no = FALSE;
	setup_vars->so = FALSE;
	setup_vars->ea = FALSE;
	setup_vars->we = FALSE;
	setup_vars->f = FALSE;
	setup_vars->c = FALSE;
}

int	setup_found(t_cub_ok setup_vars)
{
	if (setup_vars.no == FALSE || setup_vars.so == FALSE)
		return (FALSE);
	if (setup_vars.ea == FALSE || setup_vars.we == FALSE)
		return (FALSE);
	if (setup_vars.c == FALSE || setup_vars.f == FALSE)
		return (FALSE);
	return (TRUE);
}

int	check_filepath(char **cub, int *setup_var, t_read *reading, char (*err)[50])
{
	int	fd;

	if (ft_strlen(reading->str) < 5)
	{
		ft_strlcpy(*err, "Invalid texture path",
			ft_strlen("Invalid texture path") + 1);
		reading->return_value = FALSE;
		return (FALSE);
	}
	*cub = malloc(sizeof(char) * (ft_strlen(ft_skip_ws(&reading->str[3])) + 1));
	if (malloc_err(*cub, &reading->return_value, err))
		return (FALSE);
	ft_strlcpy(*cub, ft_skip_ws(&reading->str[3]), (ft_strlen(ft_skip_ws(&reading->str[3])) + 1));
	fd = open(*cub, O_RDONLY);
	if (fd == -1)
	{
		ft_strlcpy(*err, "Invalid texture path",
			ft_strlen("Invalid texture path") + 1);
		reading->return_value = FALSE;
		return (FALSE);
	}
	*setup_var = TRUE;
	return (TRUE);
}

int	ft_split_count(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
		i++;
	return (i);
}

int	is_rgb_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i++]))
			return (FALSE);
	}
	if (ft_atoi(str) > 255)
		return (FALSE);
	return (TRUE);
}

int	check_rgb(int (*cub)[3], int *setup_var, t_read *reading, char (*err)[50])
{
	char	**split;

	split = NULL;
	split = ft_split(ft_skip_ws(&reading->str[3]), ',');
	if (!split)
	{
		ft_strlcpy(*err, "Not enough memory", ft_strlen("Not enough memory")
			+ 1);
		reading->return_value = FALSE;
		return (FALSE);
	}
	if (ft_split_count(split) != 3 || !is_rgb_num(split[0])
		|| !is_rgb_num(split[1]) || !is_rgb_num(split[2]))
	{
		ft_strlcpy(*err, "Invalid RGB value", ft_strlen("Invalid RGB value")
			+ 1);
		reading->return_value = FALSE;
		ft_free_split(split);
		return (FALSE);
	}
	(*cub)[0] = ft_atoi(split[0]);
	(*cub)[1] = ft_atoi(split[1]);
	(*cub)[2] = ft_atoi(split[2]);
	ft_free_split(split);
	*setup_var = TRUE;
	return (TRUE);
}

int	line_valid(t_read *reading, t_cub *cub, t_cub_ok *setup_vars,
		char (*err)[50])
{
	if (reading->str == NULL)
		return (TRUE);
	if (ft_strncmp(reading->str, "NO", 2) == 0 && reading->str[2] == ' ')
		return (check_filepath(&cub->no, &setup_vars->no, reading, err));
	if (ft_strncmp(reading->str, "SO", 2) == 0 && reading->str[2] == ' ')
		return (check_filepath(&cub->so, &setup_vars->so, reading, err));
	if (ft_strncmp(reading->str, "WE", 2) == 0 && reading->str[2] == ' ')
		return (check_filepath(&cub->we, &setup_vars->we, reading, err));
	if (ft_strncmp(reading->str, "EA", 2) == 0 && reading->str[2] == ' ')
		return (check_filepath(&cub->ea, &setup_vars->ea, reading, err));
	if (ft_strncmp(reading->str, "F", 1) == 0 && reading->str[1] == ' ')
		return (check_rgb(&cub->f, &setup_vars->f, reading, err));
	if (ft_strncmp(reading->str, "C", 1) == 0 && reading->str[1] == ' ')
		return (check_rgb(&cub->c, &setup_vars->c, reading, err));
	reading->return_value = FALSE;
	ft_strlcpy(*err, "Invalid Line", ft_strlen("Invalid Line") + 1);
	return (FALSE);
}

void	free_str(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
}

void	free_cub(t_cub *cub)
{
	free_str(&cub->no);
	free_str(&cub->so);
	free_str(&cub->we);
	free_str(&cub->ea);
	free_str(&cub->map_str);
}

void	setup_vars_check(t_cub *cub, t_read *reading, t_cub_ok *setup_vars,
		char (*err)[50])
{
	while (reading->bytes > 0 && !setup_found(*setup_vars))
	{
		if (reading->buf == '\n')
		{
			if (!line_valid(reading, cub, setup_vars, err))
				break ;
			if (reading->str)
				free(reading->str);
			reading->str = NULL;
			reading->i = 0;
		}
		else
		{
			reading->str = ft_realloc(reading->str, reading->i + 2);
			if (malloc_err(reading->str, &reading->return_value, err))
				break ;
			reading->str[reading->i++] = reading->buf;
			reading->str[reading->i] = '\0';
		}
		reading->bytes = read(reading->fd, &reading->buf, 1);
	}
}

void	setup_map_str(t_cub *cub, t_read *reading, char (*err)[50])
{
	reading->i = 0;
	while (reading->bytes > 0 && reading->buf == '\n')
		reading->bytes = read(reading->fd, &reading->buf, 1);
	while (reading->bytes > 0)
	{
		cub->map_str = ft_realloc(cub->map_str, reading->i + 2);
		if (malloc_err(cub->map_str, &reading->return_value, err))
			break ;
		cub->map_str[reading->i] = reading->buf;
		cub->map_str[reading->i + 1] = '\0';
		reading->bytes = read(reading->fd, &reading->buf, 1);
		if (reading->buf == '\n' && cub->map_str[reading->i] == '\n')
		{
			ft_strlcpy(*err, "Forbidden newline in map",
				ft_strlen("Forbidden newline in map") + 1);
			reading->return_value = FALSE;
			break ;
		}
		reading->i++;
	}
}

void	init_reading(t_read *reading)
{
	reading->return_value = TRUE;
	reading->str = NULL;
	reading->i = 0;
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

void	init_data(t_data *data)
{
	data->err[0] = '\0';
	data->map = NULL;
}

void	count_map_row_col(char *str, int *max_col, int *max_row)
{
	int	i;
	int	col;

	i = 0;
	col = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			if (col > *max_col)
				*max_col = col;
			(*max_row)++;
			col = 0;
		}
		else
			col++;
		i++;
	}
	(*max_row)++;
	if (str[i - 1] == '\n')
		(*max_row)--;
}

void	init_map(t_map *map)
{
	map->grid = NULL;
	map->col_max = 0;
	map->row_max = 0;
	map->i = 0;
	map->j = 0;
}

void print_grid(t_map *map)
{
	int i;
	int j;

	i = 0;
	while (i < map->row_max)
	{
		j = 0;
		while (j < map->col_max)
		{
			ft_printf("%i", map->grid[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

void	free_grid(int ***grid, int max_row)
{
	int	i;

	i = 0;
	if ((*grid))
	{
		while (i < max_row)
			free((*grid)[i++]);
		free((*grid));
		*grid = NULL;
	}
}

void	create_grid(t_map *map)
{
	int	i;

	i = 0;
	map->grid = malloc(sizeof(int *) * map->row_max);
	if (!map->grid)
		return ;
	while (i < map->row_max)
	{
		map->grid[i] = malloc(sizeof(int) * map->col_max);
		if (!map->grid[i])
		{
			free_grid(&map->grid, i);
			break ;
		}
		++i;
	}
}

void	free_map(t_map *map)
{
	if (map)
	{
		free_grid(&map->grid, map->row_max);
		free(map);
	}
}

void	newline_grid(t_map *map)
{
	while (map->i < map->col_max)
		map->grid[map->j][map->i++] = -1;
	map->i = 0;
	++map->j;
}

int	fill_grid(char *str, t_map *map, char (*err)[50])
{
	int	s_i;

	s_i = -1;
	while (str[++s_i])
	{
		if (str[s_i] == ' ')
			map->grid[map->j][map->i++] = -1;
		else if (str[s_i] == '1')
			map->grid[map->j][map->i++] = 1;
		else if (str[s_i] == '0')
			map->grid[map->j][map->i++] = 0;
		else if (str[s_i] == 'N' || str[s_i] == 'E' || str[s_i] == 'S'
			|| str[s_i] == 'W')
			{
				map->grid[map->j][map->i++] = 2;
			}
		else if (str[s_i] == '\n')
			newline_grid(map);
		else
		{
			ft_strlcpy(*err, "Wrong char", ft_strlen("Wrong char") + 1);
			return (FALSE);
		}
	}
	while (map->i < map->col_max)
		map->grid[map->j][map->i++] = -1;
	map->i = 0;
	map->j = 0;
	return (TRUE);
}

void	check_edge(t_map *map, int *return_value, char (*err)[50])
{
	if (!(map->grid[map->j][map->i] == -1 || map->grid[map->j][map->i] == 1))
	{
		ft_strlcpy(*err, "Edge of map has to be walls",
			ft_strlen("Edge of map has to be walls") + 1);
		*return_value = FALSE;
	}
}

void	check_mid(t_map *map, int *return_value, int *player_count,
		char (*err)[50])
{
	if ((map->grid[map->j - 1][map->i] == -1 || map->grid[map->j + 1][map->i] ==
			-1 || map->grid[map->j][map->i - 1] == -1
			|| map->grid[map->j][map->i + 1] == -1)
		&& !(map->grid[map->j][map->i] == -1 || map->grid[map->j][map->i] == 1))
	{
		ft_strlcpy(*err, "Edge of map has to be walls",
			ft_strlen("Edge of map has to be walls") + 1);
		*return_value = FALSE;
	}
	else if ((map->grid[map->j - 1][map->i - 1] == -1 || map->grid[map->j + 1][map->i + 1] ==
			-1 || map->grid[map->j + 1][map->i - 1] == -1
			|| map->grid[map->j - 1][map->i + 1] == -1)
		&& !(map->grid[map->j][map->i] == -1 || map->grid[map->j][map->i] == 1))
			{
		ft_strlcpy(*err, "Map inner corner has to be wall",
			ft_strlen("Map inner corner has to be wall") + 1);
		*return_value = FALSE;
	}
	if (map->grid[map->j][map->i] == 2)
		(*player_count)++;	
}


int	check_grid(t_map *map, char (*err)[50])
{
	int	player_count;
	int	return_value;

	return_value = TRUE;
	player_count = 0;
	while (map->j < map->row_max)
	{
		map->i = 0;
		while (map->i < map->col_max)
		{
			if (map->j == 0 || map->j == map->row_max - 1 || map->i == 0
				|| map->i == map->col_max - 1)
				check_edge(map, &return_value, err);
			else
				check_mid(map, &return_value, &player_count, err);
			map->i++;
		}
		map->j++;
	}
	if (player_count != 1)
	{
		ft_strlcpy(*err, "Player must be 1", ft_strlen("Player must be 1") + 1);
		return_value = FALSE;
	}
	return (return_value);
}

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

/* void clean_up(t_data *data, t_cub *cub)
{

}
 */
int	main(int ac, char **av)
{
	t_data data;
	t_cub cub;

	
	init_data(&data);
	init_cub(&cub);
	if (!input_validator(ac, av, &data.err) || !file_validator(av[1], &cub, &data.err)
		|| !map_validator(&data, cub, &data.err))
	{
		ft_printf_err("Error\n%s\n", data.err);
		free_cub(&cub);
		free_map(data.map);
		return (0);
	}
	ft_printf("all ok :)\n");
	free_map(data.map);
	free_cub(&cub);
	return (1);
}