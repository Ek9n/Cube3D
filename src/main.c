/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yubi42 <yubi42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 15:47:45 by yubi42            #+#    #+#             */
/*   Updated: 2024/02/26 15:37:09 by yubi42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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