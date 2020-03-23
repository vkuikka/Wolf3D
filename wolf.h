#ifndef WOLF_H
# define WOLF_H

# define R_HEX(x) ((x) * 65536)
# define G_HEX(x) ((x) * 256)
# define B_HEX(x) (x)
# define R_VAL(x) ((x) / 65536)
# define G_VAL(x) (((x) - ((x) / 65536) * 65536) / 256)
# define B_VAL(x) ((x) - ((x) / 256) * 256)

# define ESC 65307
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
	float		pos_x;
	float		pos_y;
	float		player_dir;
}				t_wolf;

#endif
