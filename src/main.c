/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 15:47:45 by yubi42            #+#    #+#             */
/*   Updated: 2024/05/02 18:18:41 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	main(int ac, char **av)
{
	t_data	data;
	
	data.sound_on = false;
	while (data.restart)
	{
		init_data(&data);
		if (!input_validator(ac, av, &data.err) || !file_validator(av[1],
				data.texture, &data.err) || !map_validator(&data, *(data.texture),
				&data.err))
		{
			ft_printf_err("Error\n%s\n", data.err);
			free_data(&data);
			return (1);
		}
		ft_printf("all ok :)\n");
		run_game(&data);
		free_data(&data);
	}
	return (0);
}
