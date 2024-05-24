/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 15:47:45 by yubi42            #+#    #+#             */
/*   Updated: 2024/05/24 17:51:34 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	get_user_name(t_data *data)
{
	char	c;
	int		i;
	int		bytes_read;

	c = 0;
	i = 0;
	printf("\033[2J");
	printf("\033[H");
	printf("\nWeLcOme TO CArRacEr!\n");
	printf("------------------------\n");
	printf("WhAt Is uR nAme DrIVeR?:\n");
	while (c != '\n' && i < 20)
	{
		bytes_read = read(STDIN_FILENO, &c, sizeof(char));
		data->name[i] = c;
		if (bytes_read == 0)
			break ;
		i++;
	}
	if (c == '\n' && i == 1)
		ft_memcpy(data->name, "noname", 7);
	else
		data->name[i - 1] = '\0';
}

int	main(int ac, char **av)
{
	t_data	data;

	data.restart = true;
	data.sound_on = true;
	ft_memcpy(data.name, "DEFAULT", 8);
	get_user_name(&data);
	while (data.restart)
	{
		init_data(&data);
		load_score(&data);
		if (!input_validator(ac, av, &data.err) || \
			!file_validator(av[1], data.texture, &data.err) || \
			!map_validator(&data, *(data.texture), &data.err))
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
