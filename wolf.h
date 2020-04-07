#ifndef WOLF_H
# define WOLF_H

# define R_HEX(x) ((x) * 65536)
# define G_HEX(x) ((x) * 256)
# define B_HEX(x) (x)
# define R_VAL(x) ((x) / 65536)
# define G_VAL(x) (((x) - ((x) / 65536) * 65536) / 256)
# define B_VAL(x) ((x) - ((x) / 256) * 256)

# define ESC 65307
# define UINT_MAX 4294967295
# define RES_X 1800
# define RES_Y 1100
# define PI 3.14159265358979323846
# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <math.h>

typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	char		*map_path;
}				t_mlx;

typedef struct	s_wolf
{
	int			**map;
	unsigned	pos_x;
	unsigned	pos_y;
	double		sub_pos_x;
	double		sub_pos_y;
	double		dir;
}				t_wolf;

#endif
