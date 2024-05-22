/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:17:50 by jborner           #+#    #+#             */
/*   Updated: 2024/05/22 22:26:34 by hstein           ###   ########.fr       */
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

int	remote_delay_ms(size_t delay)
{
	size_t			time_us;
	static size_t	time_tmp;
	static size_t	time_cnt;
	struct timeval	tv;

	delay *= 1000;
	gettimeofday(&tv, NULL);
	time_us = tv.tv_usec;
	if (time_tmp > time_us)
		time_cnt += 1000000 - time_tmp + time_us;
	else
		time_cnt += time_us - time_tmp;
	time_tmp = time_us;
	if ((time_cnt % (delay * 2)) < delay)
		return (1);
	return (0);
}

size_t	delay_ms(void)
{
	static bool		flag;
	static size_t	counter;
	size_t			delay;

	delay = 10;
	if (remote_delay_ms(delay))
		flag = true;
	if (flag == true && !remote_delay_ms(delay))
	{
		counter += 50;
		flag = false;
	}
	return (counter);
}
