/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_and_save.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jborner <jborner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 22:15:38 by hstein            #+#    #+#             */
/*   Updated: 2024/06/03 17:40:41 by jborner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	safe_score_open(void)
{
	int	fd;

	fd = open("./highscore", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	close(fd);
	fd = open("./highscore", O_WRONLY | O_APPEND, 0644);
	return (fd);
}

static void	safe_score_write(t_data *data, int fd)
{
	int	i;

	i = -1;
	while (++i < SCORE_ENTRYS)
	{
		write(fd, &data->names[i], ft_strlen(data->names[i]) + 1);
		write(fd, &data->score[i], sizeof(long long));
	}
	close(fd);
}

int	safe_score(t_data *data)
{
	int	fd;
	int	i;
	int	j;

	fd = safe_score_open();
	i = -1;
	while (++i < SCORE_ENTRYS)
	{
		if (data->score[i] == 0 || data->highscore < data->score[i])
		{
			j = SCORE_ENTRYS - 1;
			while (j > i)
			{
				data->score[j] = data->score[j - 1];
				ft_strlcpy(data->names[j], data->names[j - 1],
					ft_strlen(data->names[j - 1]) + 1);
				j--;
			}
			data->score[i] = data->highscore;
			ft_strlcpy(data->names[i], data->name, ft_strlen(data->name) + 1);
			break ;
		}
	}
	safe_score_write(data, fd);
	return (0);
}

int	load_score(t_data *data)
{
	int	fd;
	int	i;

	i = -1;
	fd = open("./highscore", O_RDONLY);
	if (fd != -1)
	{
		while (++i < SCORE_ENTRYS)
		{
			read(fd, &data->names[i], ft_strlen(data->names[i]));
			read(fd, &data->score[i], sizeof(long long));
		}
		close(fd);
	}
	else
	{
		while (++i < SCORE_ENTRYS)
		{
			ft_strlcpy(data->names[i], "DEFAULT", 8);
			data->score[i] = 0;
		}
	}
	data->highscore = 0;
	return (0);
}
