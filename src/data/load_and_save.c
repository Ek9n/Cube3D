/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_and_save.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 22:15:38 by hstein            #+#    #+#             */
/*   Updated: 2024/05/24 17:02:27 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	safe_score(t_data *data)
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

int	load_score(t_data *data)
{
	int			fd;
	int			i;

	i = -1;
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
	{
		while (++i < SCORE_ENTRYS)
		{
			ft_memcpy(data->names[i], "DEFAULT", 8);
			data->score[i] = 0;
		}
	}
	data->highscore = 0;
	return (0);
}
