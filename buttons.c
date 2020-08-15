/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 13:36:13 by vkuikka           #+#    #+#             */
/*   Updated: 2020/08/15 21:05:14 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	ft_wolf(t_player player, t_window *window)
{
	t_ray	ray;
	int		window_x;

	window_x = -1;
	ray.angle = player.angle - player.fov / 2;
	ray.increment = player.fov / (double)RES_X;
	while (++window_x < RES_X)
	{
		ray.sin = sin(RAD(ray.angle)) / RAY_PREC;
		ray.cos = cos(RAD(ray.angle)) / RAY_PREC;
		ray.x = player.pos_x + ray.cos;
		ray.y = player.pos_y + ray.sin;
		while (!(window->map[(int)(ray.y)][(int)(ray.x)]))
		{
			ray.prev_x = ray.x;
			ray.prev_y = ray.y;
			ray.x += ray.cos;
			ray.y += ray.sin;
		}
		ray.dist = sqrt(pow(player.pos_x - ray.x, 2) +
			pow(player.pos_y - ray.y, 2)) * cos(RAD(ray.angle - player.angle));
		ft_draw_line(window_x, (int)(RES_Y / ray.dist), window, ray);
		ray.angle += ray.increment;
	}
}

Uint32	ft_get_pixel(SDL_Surface *surface, int x, int y)
{
	int		bpp;
	Uint8	*p;

	bpp = surface->format->BytesPerPixel;
	p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	if (bpp == 1)
		return (*p);
	else if (bpp == 2)
		return (*(Uint16 *)p);
	else if (bpp == 3)
	{
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return (p[0] << 16 | p[1] << 8 | p[2]);
		else
			return (p[0] | p[1] << 8 | p[2] << 16);
	}
	else if (bpp == 4)
		return (*(Uint32 *)p);
	return (0);
}

void	ft_deal_key(int key, t_window *window, t_player *p)
{
	double			new_x;
	double			new_y;
	int				dir;

	dir = key == A_KEY || key == S_KEY || key == Q_KEY ? -1 : 1;
	if (key == Q_KEY || key == E_KEY)
	{
		p->angle += dir * ROT_SPEED;
		return ;
	}
	new_x = p->pos_x + ((double)dir * cos(RAD(p->angle))) * MOVE_SPEED;
	new_y = p->pos_y + ((double)dir * sin(RAD(p->angle))) * MOVE_SPEED;
	if (key == A_KEY || key == D_KEY)
	{
		new_x = p->pos_x + cos(RAD(p->angle + (90 * dir))) * (MOVE_SPEED / 2);
		new_y = p->pos_y + sin(RAD(p->angle + (90 * dir))) * (MOVE_SPEED / 2);
	}
	if (!window->map[(int)(new_y - 0.1)][(int)(new_x - 0.1)] &&
		!window->map[(int)(new_y + 0.1)][(int)(new_x + 0.1)])
	{
		p->pos_x = new_x;
		p->pos_y = new_y;
	}
}

int		ft_buttons(int button, const int pressed)
{
	static int		*keys;
	int				i;

	if (!(keys) && (i = -1))
	{
		if (!(keys = (int *)malloc(sizeof(int) * SAME_TIME_BUTTONS)))
			ft_error("memory allocation failed\n");
		while (++i < SAME_TIME_BUTTONS)
			keys[i] = -1;
	}
	i = -1;
	while (++i < SAME_TIME_BUTTONS)
		if (pressed == -1 && keys[i] == button)
			return (1);
		else if (pressed == 0 && keys[i] == button)
		{
			keys[i] = -1;
			return (0);
		}
		else if (pressed == 1 && keys[i] == -1)
		{
			keys[i] = button;
			return (0);
		}
	return (0);
}

int		ft_loop(t_window *window)
{
	if (ft_buttons(W_KEY, -1) || ft_buttons(ARROW_U, -1))
		ft_deal_key(W_KEY, window, &window->player);
	if (ft_buttons(A_KEY, -1))
		ft_deal_key(A_KEY, window, &window->player);
	if (ft_buttons(S_KEY, -1) || ft_buttons(ARROW_D, -1))
		ft_deal_key(S_KEY, window, &window->player);
	if (ft_buttons(D_KEY, -1))
		ft_deal_key(D_KEY, window, &window->player);
	if (ft_buttons(NUM1, -1) && window->player.fov > -180)
		window->player.fov--;
	if (ft_buttons(NUM2, -1) && window->player.fov < 180)
		window->player.fov++;
	if (ft_buttons(Q_KEY, -1) || ft_buttons(ARROW_L, -1))
		ft_deal_key(Q_KEY, window, &window->player);
	if (ft_buttons(E_KEY, -1) || ft_buttons(ARROW_R, -1))
		ft_deal_key(E_KEY, window, &window->player);
	SDL_SetRenderDrawColor(window->SDLrenderer, 0, 0, 0, 255);
	SDL_RenderClear(window->SDLrenderer);
	ft_wolf(window->player, window);
	SDL_RenderPresent(window->SDLrenderer);
	return (0);
}
