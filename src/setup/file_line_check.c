/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_line_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jborner <jborner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:08:21 by yubi42            #+#    #+#             */
/*   Updated: 2024/05/15 15:53:06 by jborner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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
	ft_strlcpy(*cub, ft_skip_ws(&reading->str[3]),
		(ft_strlen(ft_skip_ws(&reading->str[3])) + 1));
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

int	err_rgb(t_read *reading, char (*err)[50], char **split, char *msg)
{
	ft_strlcpy(*err, msg, ft_strlen(msg) + 1);
	reading->return_value = FALSE;
	ft_free_split(split);
	return (FALSE);
}

int	check_rgb(int (*cub)[3], int *setup_var, t_read *reading, char (*err)[50])
{
	char	**split;

	split = NULL;
	split = ft_split(ft_skip_ws(&reading->str[2]), ',');
	if (!split)
		return (err_rgb(reading, err, split, "Not enough memory"));
	if (ft_split_count(split) != 3 || !is_rgb_num(split[0])
		|| !is_rgb_num(split[1]) || !is_rgb_num(split[2]))
		return (err_rgb(reading, err, split, "Invalid RGB value"));
	(*cub)[0] = ft_atoi(split[0]);
	(*cub)[1] = ft_atoi(split[1]);
	(*cub)[2] = ft_atoi(split[2]);
	ft_free_split(split);
	*setup_var = TRUE;
	return (TRUE);
}

int	line_valid(t_read *reading, t_texture *cub, t_texture_ok *setup_vars,
		char (*err)[50])
{
	if (reading->str == NULL)
		return (TRUE);
	if (ft_strncmp(reading->str, "NO", 2) == 0 && reading->str[2] == ' ')
		return (check_filepath(&cub->no_path, &setup_vars->no, reading, err));
	if (ft_strncmp(reading->str, "SO", 2) == 0 && reading->str[2] == ' ')
		return (check_filepath(&cub->so_path, &setup_vars->so, reading, err));
	if (ft_strncmp(reading->str, "WE", 2) == 0 && reading->str[2] == ' ')
		return (check_filepath(&cub->we_path, &setup_vars->we, reading, err));
	if (ft_strncmp(reading->str, "EA", 2) == 0 && reading->str[2] == ' ')
		return (check_filepath(&cub->ea_path, &setup_vars->ea, reading, err));
	if (ft_strncmp(reading->str, "F", 1) == 0 && reading->str[1] == ' ')
		return (check_rgb(&cub->f, &setup_vars->f, reading, err));
	if (ft_strncmp(reading->str, "C", 1) == 0 && reading->str[1] == ' ')
		return (check_rgb(&cub->c, &setup_vars->c, reading, err));
	reading->return_value = FALSE;
	ft_strlcpy(*err, "Invalid Line", ft_strlen("Invalid Line") + 1);
	return (FALSE);
}
