/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yubi42 <yubi42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 15:47:45 by yubi42            #+#    #+#             */
/*   Updated: 2024/05/06 14:43:35 by yubi42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int safe_score(t_data *data)
{
	int	fd;

	fd = open("./highscore", O_WRONLY /* | O_APPEND */ | O_CREAT, 0644);
	write(fd, &data->highscore, sizeof(size_t));
	close(fd);
	return (0);
}

int load_score(t_data *data)
{
	// nummern immer size_t gross.. bei 100 nummern wird alles gelesen und dann durch size geteilt.. dann hat man die anzahl der nummern...
	// oder einfach fest sagen.. zb 10 eintraege hat der highscore.. dann kann man genau 10 * sizeof(size_t) lesen.. wenn es erst 2 scores gibt sind die anderen 999999 .. oder 0 oder so
	int	fd;

	fd = open("./highscore", O_RDONLY);
	read(fd, &data->highscore, sizeof(size_t));
	close(fd);
	ft_printf("score is %zu\n", data->highscore);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;
	
	data.restart = true;
	while (data.restart)
	{
		init_data(&data);
		load_score(&data);
		if (!input_validator(ac, av, &data.err) || !file_validator(av[1],
				data.texture, &data.err) || !map_validator(&data, *(data.texture),
				&data.err))
		{
			ft_printf_err("Error\n%s\n", data.err);
			free_data(&data);
			return (1);
		}
		data.sound_on = true;
		ft_printf("all ok :)\n");
		run_game(&data);
		// safe_score(&data);
		free_data(&data);
	}
	return (0);
}
