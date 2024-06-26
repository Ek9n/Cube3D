/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jborner <jborner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 12:12:36 by yubi42            #+#    #+#             */
/*   Updated: 2024/06/03 15:12:44 by jborner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "../lib/libft/libft.h"
# include "./miniaudio.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <mlx.h>
# include <mlx_int.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

# define TRUE 1
# define FALSE 0
# define PI 3.1415926535
# define IMG_SIZE 64

# define TRANS 0x000000
# define GREEN 0xFF00
# define PURPLE 0xFF00FF
# define YELLOW 0xFFFF00
# define BLACK 0x000001
# define WHITE 0xFFFFFF
# define RED 0xFF0000
# define LIME 0x00FF00
# define BLUE 0x0000FF
# define MOVSPEED 1
# define NUM_KEYS 65536
# define ANIM_DELAY 6
# define ROT_MIN 0
# define ROT_MAX 15
# define MOV_MAX 100
# define MOV_MIN 10
# define SIDESTEP 10
# define EPSILON 1e-6
# define MINIMAP_WIDTH 15
# define MINIMAP_HEIGHT 9
# define ROUNDS 2
# define SCORE_ENTRYS 10

typedef struct s_read
{
	int				fd;
	char			buf;
	ssize_t			bytes;
	char			*str;
	int				i;
	int				return_value;
}					t_read;

typedef struct s_image
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		endian;
	int		bytes_per_line;
	int		width;
	int		height;
	int		x;
	int		y;
	int		z;
}					t_image;

typedef struct s_minimap
{
	t_image			*base;
	t_image			*resize;
	t_image			*small;
	int				resize_value;
	t_image			*wall;
	t_image			*ground;
	t_image			*player;
	t_image			*player_rot;
	t_image			*exit;

}					t_minimap;

typedef struct s_texture
{
	t_minimap	*minimap;
	t_image		*base_img;
	t_image		*base_img2;
	t_image		*base_img2_resize;
	t_image		*backmirror;
	t_image		*backmirror2;
	t_image		*carframe;
	t_image		*carframe2;
	t_image		*steeringwheel;
	t_image		*steeringwheel2;
	t_image		*alpha;
	t_image		*alpha2;
	t_image		*num0;
	t_image		*num1;
	t_image		*num2;
	t_image		*num3;
	t_image		*num4;
	t_image		*num5;
	t_image		*num6;
	t_image		*num7;
	t_image		*num8;
	t_image		*num9;
	t_image		*slash;
	t_image		*kmh;
	t_image		*game_over;
	t_image		*your_score;
	t_image		*high_score;
	t_image		*img1;
	t_image		*img2;
	t_image		*black;
	t_image		*transparent;
	t_image		*goal;
	t_image		*no;
	t_image		*so;
	t_image		*ea;
	t_image		*we;
	t_image		*sprite1;
	char		*img_map_ground;
	char		*map_ground;
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	int			f[3];
	int			c[3];
	char		*map_str;
}	t_texture;

typedef struct s_texture_ok
{
	int				no;
	int				so;
	int				we;
	int				ea;
	int				f;
	int				c;
}	t_texture_ok;

typedef struct s_map
{
	int				**grid;
	int				row_max;
	int				col_max;
	int				i;
	int				j;
	char			player;
}	t_map;

typedef struct s_player
{
	double			x;
	double			y;
	double			dx;
	double			dy;
	double			x_sin;
	double			y_cos;
	double			angle;
	double			speed[3];
	int				rotation;
	int				rev_speed;
	int				corners[4][2];
	int				dead;
	int				wall_hit;
}	t_player;

typedef struct s_ray
{
	int				ray_amount;
	double			ray_len;
	int				img_col;
	t_image			*img;
	int				x;
	int				y;
	double			angle;
	double			sin;
	double			cos;
	double			fabs_sin;
	double			fabs_cos;
	double			row_x;
	double			row_y;
	double			col_x;
	double			col_y;
	double			row_step;
	double			col_step;
	double			row_step_x;
	double			row_step_y;
	double			col_step_x;
	double			col_step_y;
	double			first_row_step;
	double			first_col_step;
	double			dis_row;
	double			dis_col;
	int				first_col;
}	t_ray;

typedef struct s_ray_back
{
	int				ray_amount;
	double			ray_len;
	int				img_col;
	t_image			*img;
	int				x;
	int				y;
	double			angle;
	double			sin;
	double			cos;
	double			fabs_sin;
	double			fabs_cos;
	double			row_x;
	double			row_y;
	double			col_x;
	double			col_y;
	double			row_step;
	double			col_step;
	double			row_step_x;
	double			row_step_y;
	double			col_step_x;
	double			col_step_y;
	double			first_row_step;
	double			first_col_step;
	double			dis_row;
	double			dis_col;
	int				first_col;
}	t_ray_back;

typedef struct s_sound
{
	ma_result	result;
	ma_engine	engine;
	ma_sound	motor;
	ma_sound	crash;
	ma_sound	siren;
	ma_sound	soundtrack;
}	t_sound;

typedef struct s_line
{
	long long	xy0[2];
	long long	xy1[2];
	long long	m;
	long long	x;
	long long	y;
	long long	b;
}	t_line;

typedef struct s_sprite
{
	int	x;
	int	y;

}	t_sprite;

typedef struct s_rotate
{
	t_image	**img;
	t_image	*img_rot;
	double	radians;
	int		y;
	int		x;
	int		new_x;
	int		new_y;
	int		rotated_x;
	int		rotated_y;	
}	t_rotate;

typedef struct s_data
{
	void			*mlx;
	void			*mlx_win;
	int				width;
	int				height;
	int				keys[NUM_KEYS];
	int				rot[NUM_KEYS];
	int				rot_max;
	long long		highscore;
	long long		cur_score;
	struct timeval	start_time;
	int				siren;
	int				round;
	int				round_touch;
	int				end_reached;
	int				minimap_width;
	int				minimap_height;
	char			err[50];
	t_texture		*texture;
	t_map			*map;
	t_player		*player;
	t_ray			ray;
	t_ray_back			ray_back;
	t_sound			sound;
	t_line			line[3];
	bool			restart;
	bool			sound_on;
	long long		score[10];
	char			name[20];
	char			names[10][20];
}	t_data;

// ================= CLOSE ==================
// err.c
int					malloc_err(void *ptr, int *return_value, char (*err)[50]);
void				close_game(t_data *data, char *msg);

// free_structs.c
void				free_minimap(t_minimap *minimap, t_data *data);
void				free_texture(t_texture *texture, t_data *data);
void				free_map(t_map *map);
void				free_data(t_data *data);

// free_utils.c
void				free_str(char **str);
void				free_ptr(void **ptr);
void				free_img(t_image *img, void *mlx);
void				free_grid(int ***grid, int max_row);

// ================= CONTROL ==================
// collision_check.c
void				set_corners(t_player *player);
int					mid_coll(t_map *map, int corner1[2], int corner2[2]);
int					check_corner_collision(t_data *data, t_map *map,
						t_player *player);
void				check_collision(t_data *data);

// collision_check_utils.c
int					in_border(t_data *data);
int					calc_mod(int num);
int					check_mid_wall(t_map *map, int corner1[2], int corner2[2],
						int mod[2]);
int					calc_coll_angle(t_data *data, double *angle, int side,
						int dir);

// key_action.c
void				calc_speed(t_data *data, int sign);
void				move_player(t_data *data, int sign, int num, int other_num);
void				rotate_player(t_data *data, int sign, int num);
void				move_side(t_data *data, int sign);
void				restart_game(t_data *data, bool opt);

// keypress.c
int					destroy_window(t_data *data);
int					handle_keypress(int keysym, t_data *data);
int					handle_keyrelease(int keysym, t_data *data);
void				handle_sound_keys(t_data *data);
void				handle_keys(t_data *data);

// ============== EXECUTE =============
// render_game.c
void				render_minimap(t_data *data, t_minimap *minimap);
void				render_background(t_data *data, t_image *bg);
void				render_backmirror(t_data *data);
int					render(t_data *data);

// run_game.c
void				run_game(t_data *data);

// put_score_utils_1.c
void				put_single_num(t_data *data, unsigned int num, \
						int w, int h);
void				put_num(t_data *data, unsigned int num, int *w_h, int pos);
void				put_num_to_baseimg(t_data *data, unsigned int num, \
						int w, int h);
void				put_kmh(t_data *data, unsigned int num, int w, int h);
long long			get_elapsed_time_ms(struct timeval *start_time);

// put_score_utils_2.c
void				put_laptime_ms(t_data *data, int w, int h, long long score);
void				put_laptime_ms_rest(t_data *data, int w, int h, \
						long long score);
void				put_laptime_s(t_data *data, int w, int h, long long score);
void				put_laptime(t_data *data, int w, int h, int highscore);
void				put_highscore(t_data *data, int w, int h);

// put_str_utils.c
void				put_letter(t_data *data, char letter, int w, int h);
void				put_str(t_data *data, char *str, int w, int h);

// ================= MINIMAP ==================
// create_minimap.c
void				draw_ray(t_data *data);
void				create_minimap_texture(t_minimap *minimap, t_data *data);
void				copy_to_small(int player_row, int player_col, t_image *full,
						t_image *part);
void				create_minimap(t_data *data);

// ================= MLX ==================
// mlx_init.c
void				init_img(t_image *img);
t_image				*create_img(t_data *data, char *path, int w, int h);
void				mlx_init_game(t_data *data);

// ============== RAYS ==============
// cast_rays_back.c
int					do_row_step_back(t_data *data, t_ray_back *ray);
int					do_col_step_back(t_data *data, t_ray_back *ray);
void				cast_ray_back(t_data *data, double angle, int x, int y);
void				cast_rays2(t_data *data, double angle, int deg, int amount);

// cast_rays.c
int					do_row_step(t_data *data, t_ray *ray);
int					do_col_step(t_data *data, t_ray *ray);
void				cast_ray(t_data *data, double angle, int x, int y);
void				cast_rays(t_data *data, double angle, int deg, int amount);

// init_ray_checker_back.c
void				init_ray_steps_back(t_ray_back *ray);
void				init_next_steps_back(t_ray_back *ray);
void				init_check_ray_back(t_ray_back *ray, double angle, int x, int y);

// init_ray_checker.c
void				init_ray_steps(t_ray *ray);
void				init_next_steps(t_ray *ray);
void				init_check_ray(t_ray *ray, double angle, int x, int y);

// ray_checker_utils.c
double				distance(double x1, double y1, double x2, double y2);
void				adjust_angle(double *angle);
void				adjust_x_y(t_data *data, double *x, double *y);

// wall_detection.c
int					wall_found(t_data *data, double cur_x, double cur_y);

//wall_detection_back.c
int					wall_found_back(t_data *data, double cur_x, double cur_y);

// ============== RENDER UTILS ==============
// draw_pixel.c
void				fill_img_color(t_image *img, int color);
void				img_pix_put(t_image *img, int x, int y, int color);
void				put_pixel_img(t_image *img, int x, int y, int color);
unsigned int		get_pixel_img(t_image *img, int x, int y);
void				put_img_to_img(t_image *dst, t_image *src, int x, int y);
void				put_img_to_img2(t_image *dst, t_image *src, int x, int y);

// fps.c
void				fps_delay(int fps);
int					remote_delay_ms(size_t delay);
size_t				delay_ms(void);

// render_utils.c
void				create_frame(t_image *img, int size, int color);
unsigned long		rgb_to_hex(int rgb[3]);
void				render_default_minimap(t_data *data, \
						t_minimap *minimap);
void				render_minimap(t_data *data, \
						t_minimap *minimap);
void				render_background(t_data *data, \
						t_image *bg);

// resize_img.c
void				scale_img(t_image **old, t_image **new, int w, int h);
void				resize_same_img(t_data *data, t_image **img, int w, int h);
t_image				*resize_img(t_data *data, t_image **old, int w, int h);

// rotate_utils.c
double				calc_old_x(t_data *data, t_image **old, int x, int y);
double				calc_old_y(t_data *data, t_image **old, int x, int y);
void				rotate_player_img(t_data *data, t_image **old,
						t_image **new);
void				rotate_wheel(t_rotate *rot);
void				rotate_stuff(t_data *data, t_image **img, \
						double angle, int opt);

// ================= SETUP ==================
// file_check.c
int					setup_found(t_texture_ok setup_vars);
void				setup_vars_check(t_texture *cub, t_read *reading,
						t_texture_ok *setup_vars, char (*err)[50]);
void				setup_map_str(t_texture *cub, t_read *reading,
						char (*err)[50]);

// file_line_check.c
int					check_filepath(char **cub, int *setup_var, t_read *reading,
						char (*err)[50]);
int					is_rgb_num(char *str);
int					check_rgb(int (*cub)[3], int *setup_var, t_read *reading,
						char (*err)[50]);
int					line_valid(t_read *reading, t_texture *cub,
						t_texture_ok *setup_vars, char (*err)[50]);

// generate_goal
void				opt1_fill_start(t_map *map, int k, int opt);
void				opt2_fill_start(t_map *map, int k, int opt);
void				choose_fill_start(t_map *map, int c);
void				set_start(t_map *map);

// init_data_struct.c
void				init_map(t_map *map);
void				init_player(t_player *player);
void				init_array(int array[NUM_KEYS], int num, int num2);
void				init_in_data_structs(t_data *data);
void				init_data(t_data *data);

// init_other_structs.c
void				init_setup_vars(t_texture_ok *setup_vars);
void				init_reading(t_read *reading);
void				init_minimap(t_minimap *minimap);
void				init_3d_textures(t_texture *texture);
void				init_texture(t_texture *texture);

// map_grid_check.c
void				check_edge(t_map *map, int *return_value, char (*err)[50]);
void				check_mid(t_map *map, int *return_value, int *player_count,
						char (*err)[50]);
int					check_grid(t_map *map, char (*err)[50]);
void				print_grid(t_map *map);

// map_grid_create_n_fill.c
void				count_map_row_col(char *str, int *max_col, int *max_row);
void				create_grid(t_map *map);
void				newline_grid(t_map *map);
int					fill_grid(char *str, t_map *map, t_player *player,
						char (*err)[50]);
int					fill_grid(char *str, t_map *map, t_player *player,
						char (*err)[50]);

// validators.c
int					map_validator(t_data *data, t_texture cub, char (*err)[50]);
int					file_validator(char *file, t_texture *cub, char (*err)[50]);
int					input_validator(int ac, char **av, char (*err)[50]);

// ================= SOUND =================
// sound.c
int					init_sounds_1(t_sound *sound);
void				setup_sounds(t_data *data);
void				terminate_sounds(t_data *data);

// ================= DATA =================
// load_and_save.c
int					safe_score(t_data *data);
int					load_score(t_data *data);

#endif
