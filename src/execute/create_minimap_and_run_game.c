
void    create_minimap(t_data *data)
{
	int col;
	int row;
	int	z;

	z = 0;
	col = -1;
	row = -1;

	while (z < 3)
	{
		while(++row < data->map->row_max)
		{
			while(++col < data->map->col_max)
			{
				if (z == 0 && data->map->grid[row][col] == 0)
					put_img_to_img(data->texture->base_img, data->texture->ea, col * IMG_SIZE, row * IMG_SIZE);
				else if (z == 1 && data->map->grid[row][col] == 1)
					put_img_to_img(data->texture->base_img, data->texture->we, col * IMG_SIZE, row * IMG_SIZE);
				else if (z == 2 && data->map->grid[row][col] == 2)
					put_img_to_img(data->texture->base_img, data->texture->no, col * IMG_SIZE, row * IMG_SIZE);
			}
			col = -1;
		}
		row = -1;
		z++;
	}
}

void	run_game(t_data *data)
{
	mlx_init_game(data);
	printf("(run_game) hi :-) width:%d, height:%d\n", data->width, data->height);

	print_grid(data->map);

	data->texture->base_img = create_img(data, NULL, data->width, data->height);
	// data->texture->img1 = create_img(data, NULL, 64, 64);
	create_minimap(data);

	// Make img green:
	// for (int y = 0; y < data->width; y++)
	// {
	// 	for (int x = 0; x < data->height; x++)
	// 		img_pix_put(data->texture->base_img, y, x, GREEN);
	// }

	// img_pix_put(data->texture->img1, 32, 32, PURPLE);
	// put_img_to_img(data->texture->base_img, data->texture->img1, 0, 0);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->texture->base_img->img_ptr, 0, 0);

	printf("rows:%d, cols:%d\n", data->map->row_max, data->map->col_max);
	mlx_hook(data->mlx_win, KeyPress, KeyPressMask, &handle_keypress, data);

	mlx_loop(data->mlx);
}
