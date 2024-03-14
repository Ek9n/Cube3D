/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yubi42 <yubi42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 15:47:45 by yubi42            #+#    #+#             */
/*   Updated: 2024/03/13 22:21:40 by yubi42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	main(int ac, char **av)
{
	t_data data;

	init_data(&data);
	if (!input_validator(ac, av, &data.err) || !file_validator(av[1], data.texture, &data.err)
		|| !map_validator(&data, *(data.texture), &data.err))
	{
		ft_printf_err("Error\n%s\n", data.err);
		free_data(&data);
		return (1);
	}
	ft_printf("all ok :)\n");
	run_game(&data);
	free_data(&data);
	return (0);
}
