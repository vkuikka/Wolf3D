/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 18:28:50 by vkuikka           #+#    #+#             */
/*   Updated: 2020/08/07 20:20:39 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# define R_HEX(x) ((x) * 65536)
# define G_HEX(x) ((x) * 256)
# define B_HEX(x) (x)
# define R_VAL(x) ((x) / 65536)
# define G_VAL(x) (((x) - ((x) / 65536) * 65536) / 256)
# define B_VAL(x) ((x) - ((x) / 256) * 256)

# define UINT_MAX 4294967295
# define SAME_TIME_BUTTONS 3
// # define RES_X 1800
// # define RES_Y 1100
# define RES_X 1000
# define RES_Y 600
# define PI M_1_PI
// # define PI 3.14159265358979323846

// rad = rad * 180 / PI
# define RAD(x) ((x) * (PI / 180))
# define DEG(x) ((x) * (180 / PI))

# define RAY_PREC 400

// # define ESC 65307
# define ESC 53
# define W_KEY 13
# define A_KEY 0
# define S_KEY 1
# define D_KEY 2
# define Q_KEY 12
# define E_KEY 14
# define ARROW_L 123
# define ARROW_R 124
# define ARROW_U 126
# define ARROW_D 125
# define NUM1 18
# define NUM2 19
# define NUM3 20
# define NUM4 21
# define NUM5 23
# define NUM6 22
# define NUM7 26
# define NUM8 28
# define NUM9 25
# define NUM0 29
# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"
// # include "Frameworks/SDL2.framework/Headers/SDL.h"
# include <fcntl.h>
# include <math.h>

typedef struct		s_player
{
	double			pos_x;
	double			pos_y;
	double			angle;
	double			fov;
	double			move_speed;
	double			rot_speed;
}					t_player;

typedef struct		s_window
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*image;
	int				bits_per_pixel;
	int				size_of_line;
	int				endian;
	char			*pixel_col;
	struct s_player	player;
	int				**map;
}					t_window;

typedef struct		s_ray
{
	double			x;
	double			y;
	double			sin;
	double			cos;
	double			angle;
	double			increment;
	double			dist;
	int				wall_code;
}					t_ray;

void		ft_wolf(t_player player, t_window *window);
void		ft_wolf_line(int x, int len, t_window *window, unsigned c);

int			ft_loop(t_window *window);
int			ft_buttons(int button, void *nothing);

void		ft_error(char *message);

void		ft_pixel(int x, int y, int color, t_window *window);
void		ft_draw_window(t_window *window);
void		ft_clear(t_window *window);

#endif
