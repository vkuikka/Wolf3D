/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 18:28:50 by vkuikka           #+#    #+#             */
/*   Updated: 2020/08/08 16:12:02 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# define R_VAL(x) ((x) / 256 / 256)
# define G_VAL(x) (((x) - ((x) / (256 * 256)) * 256 * 256) / 256)
# define B_VAL(x) ((x) - ((x) / 256) * 256)

# define SAME_TIME_BUTTONS 3
# define RAY_PREC 400
# define RES_X 800
# define RES_Y 500

# define PI M_PI
# define RAD(x) ((x) * (PI / 180))
# define DEG(x) ((x) * (180 / PI))

#define APL_SDL2
#ifdef APL_SDL2
# define ESC 41
# define W_KEY 26
# define A_KEY 4
# define S_KEY 22
# define D_KEY 7
# define Q_KEY 20
# define E_KEY 8
# define ARROW_U 82
# define ARROW_L 80
# define ARROW_D 81
# define ARROW_R 79
# define NUM1 30
# define NUM2 31
# define NUM3 32
# define NUM4 33
# define NUM5 34
# define NUM6 35
# define NUM7 36
# define NUM8 37
# define NUM9 38
# define NUM0 39
#endif

#ifdef APL_MLX
# define R_HEX(x) ((x) * 65536)
# define G_HEX(x) ((x) * 256)
# define B_HEX(x) (x)
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
#endif

#ifdef LNX_MLX
# define ESC 65307
#endif

# include <math.h>
# include <fcntl.h>
# include "get_next_line.h"
# include "Output/SDL2.framework/Headers/SDL.h"

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
	struct s_player	player;
	int				**map;
	SDL_Renderer	*SDLrenderer;
	SDL_Window		*SDLwindow;
}					t_window;

typedef struct		s_ray
{
	double			x;
	double			y;
	double			prev_x;
	double			prev_y;
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
int			ft_buttons(int button, int pressed);
void		ft_error(char *message);
void		ft_draw_window(t_window *window);
void		ft_clear(t_window *window);

#endif
