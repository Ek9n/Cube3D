/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 15:47:45 by yubi42            #+#    #+#             */
/*   Updated: 2024/05/15 14:39:07 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int safe_score(t_data *data)
{
	int	fd;
	int	i;
	int	j;

	fd = open("./highscore", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	close(fd);
	fd = open("./highscore", O_WRONLY | O_APPEND, 0644);
	i = -1;
	while (++i < SCORE_ENTRYS)
	{
		if (data->score[i] == 0 || data->highscore < data->score[i])
		{
			j = SCORE_ENTRYS - 1;
			while (j > i)
			{
				data->score[j] = data->score[j - 1];
				ft_memcpy(data->names[j], data->names[j - 1], 20);
				j--;
			}
			data->score[i] = data->highscore;
			ft_memcpy(data->names[i], data->name, sizeof(data->name));
			printf("NAME:%s\n", data->name);
			// if (i + 1 < SCORE_ENTRYS && data->cur_score < data->score[i + 1])
			// 	data->score[i + 1] = data->cur_score;
			break ;
		}
	}
	i = -1;
	while (++i < SCORE_ENTRYS)
	{
		write(fd, &data->names[i], 20);
		write(fd, &data->score[i], sizeof(long long));
	}
	close(fd);
	return (0);
}

int load_score(t_data *data)
{
	int	fd;
	int	i = -1;
	long long	null = 0;

	fd = open("./highscore", O_RDONLY);
	if (fd != -1)
	{
		while (++i < SCORE_ENTRYS)
		{
			read(fd, &data->names[i], 20);
			read(fd, &data->score[i], sizeof(long long));
		}
		close(fd);
	}
	else
		while (++i < SCORE_ENTRYS)
		{
			ft_memcpy(data->names[i], "DEFAULT", 8);
			data->score[i] = 0;
		}
	// printf("HIGHSCORE:\n");
	i = -1;
	while (++i < SCORE_ENTRYS)
	{
		printf("%s\n", data->names[i]);
		printf("%lld\n", data->score[i]);
	}
	// data->highscore = data->score[0];
	data->highscore = 0;
	return (0);
}

void	reset_elapsed_time(struct timeval *start_time)
{
	start_time->tv_sec = 0;
	start_time->tv_usec = 0;
}

void	get_user_name(t_data *data)
{
    // char buffer[20]; // Puffer für die Eingabe
	char c = 0;
	int i = 0;
    ssize_t bytesRead; // Anzahl der gelesenen Bytes

	printf("INPuT:\n");

    // Daten von stdin lesen
	while (c != '\n' && i < 20)
	{
		bytesRead = read(STDIN_FILENO, &c, sizeof(char));
		data->name[i] = c;
		if (bytesRead == 0)
			break ;
		i++;
	}
	if (c == '\n' && i == 1)
		ft_memcpy(data->name, "noname", 7);
	else
		data->name[i - 1] = '\0';

	printf("INPuT:%s\n", data->name);
}

int	main(int ac, char **av)
{
	t_data	data;

	data.restart = true;
	ft_memcpy(data.name, "DEFAULT", 8);
	get_user_name(&data);
	while (data.restart)
	{
		init_data(&data);
		// reset_elapsed_time(&data.start_time);

		load_score(&data);

		// safe_score(&data);
		// close_game(&data, NULL);
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
		free_data(&data);
		// data.start_time = data.cur_score;
	}
	return (0);
}
