#ifndef WOLF_H
# define WOLF_H

# define R_HEX(x) ((x) * 65536)
# define G_HEX(x) ((x) * 256)
# define B_HEX(x) (x)
# define R_VAL(x) ((x) / 65536)
# define G_VAL(x) (((x) - ((x) / 65536) * 65536) / 256)
# define B_VAL(x) ((x) - ((x) / 256) * 256)

# define UINT_MAX 4294967295
// # define RES_X 1800
// # define RES_Y 1100
# define RES_X 1800
# define RES_Y 1100
# define PI M_1_PI
// # define PI 3.14159265358979323846

// rad = rad * 180 / PI
# define RAD(x) ((x) * (PI / 180))
# define DEG(x) ((x) * (180 / PI))

# define RAY_PREC 100

// # define ESC 65307
# define ESC 53
# define UP 13
# define DOWN 1
# define LEFT 0
# define RIGHT 2
# define TURN_LEFT 12
# define TURN_RIGHT 14
# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <math.h>

typedef struct		s_window
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*image;
	int				bits_per_pixel;
	int				size_of_line;
	int				endian;
	char			*pixel_col;
}					t_window;

typedef struct		s_wolf
{
	double			pos_x;
	double			pos_y;
	double			angle;
	double			fov;
	double			move_speed;
	double			rot_speed;
}					t_wolf;

void		ft_wolf_line(int x, int len, t_window *window, unsigned c);
void		ft_pixel(int x, int y, int color, t_window *window);
void		ft_draw_window(t_window *window);
void		ft_clear(t_window *window);

#endif
