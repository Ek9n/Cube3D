/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jborner <jborner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:17:50 by jborner           #+#    #+#             */
/*   Updated: 2024/05/15 15:45:01 by jborner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	fps_delay(int fps)
{
	float			interval;
	float			time_passed;
	struct timeval	cur_time;
	struct timeval	start_time;

	interval = 1.0 / fps;
	gettimeofday(&start_time, NULL);
	while (1)
	{
		gettimeofday(&cur_time, NULL);
		time_passed = (cur_time.tv_sec - start_time.tv_sec) + (cur_time.tv_usec
				- start_time.tv_usec) / 1000000.0;
		if (time_passed >= interval)
			break ;
	}
}
