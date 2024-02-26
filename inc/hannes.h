# ifndef HANNES_H
# define HANNES_H

#define WIDTH 800
#define HEIGHT 600
#define IMGSIZE 64
#define GREEN_PIXEL 0xFF00
#define PURPLE_PIXEL 0xFF00FF

typedef struct s_color
{
	int r;
	int g;
	int b;
} t_color;

// 

// typedef struct s_map
// {
// 	int num_rows;
// 	int num_cols;
// 	double a_z;
// 	double a_x;
// 	double a_y;
// 	t_coords **coords;
// } t_map;

// typedef struct s_img
// {
// 	void *mlx_img;
// 	char *addr;
// 	int bpp;
// 	int line_len; //???
// 	int endian;
// 	t_color *gradient;
// 	// t_map map;
// } t_img;

// typedef struct s_data2
// {
// 	void *mlx_ptr;
// 	void *win_ptr;
// 	t_img img;
// 	t_map map;
// 	t_map3D *map3D;
// 	int safed_mouse_x;
// 	int safed_mouse_y;
// 	bool button_pressed;
// 	bool button2_pressed;
// } t_data2;



int     draw_square(t_img *img);
void	img_pix_put(t_img *img, int x, int y, int color);
int	    remote_delay_ms(size_t delay);
size_t	delay_ms(void);

#endif