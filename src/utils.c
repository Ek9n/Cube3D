#include "cube.h"

// int	render(t_data *data)
// {
// 	static t_render_vars	lrv;

// 	if (data->win_ptr == NULL)
// 		return (MLX_ERROR);
// 	rotate(data, 0.05);
// 	translate(data);
// 	if (lrv.last_a_z != data->map.a_z || lrv.last_a_x != data->map.a_x 
// 		|| lrv.last_scale != data->map.scale 
// 		|| lrv.last_move_x != data->map.move_x 
// 		|| lrv.last_move_y != data->map.move_y 
// 		|| lrv.last_descale_z != data->map.descale_z)
// 	{
// 		mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
// 		data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
// 		data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp, 
// 				&data->img.line_len, &data->img.endian);
// 		compare_and_draw(data);
// 		handle_last_render_vars(&lrv, data);
// 		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
// 	}
// 	return (0);
// }

int draw_square(t_img *img)
{
	int side_length = 64;
	// int x = WIDTH / 2 - side_length / 2;
	// int y = HEIGHT / 2 - side_length / 2;
    int x = 0;
    int y = 0;

	for (int i = x; i < x + side_length; i++)
	{
		for (int j = y; j < y + side_length; j++)
		{
			img_pix_put(img, i, j, green);
		}
	}
	return (0);
}

void	img_pix_put(t_img *img, int x, int y, int color)
{
    char    *pixel;

    pixel = img->addr + (x * img->line_len + y * (img->bpp / 8));
    *(int *)pixel = color;
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
