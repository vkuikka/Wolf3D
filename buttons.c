/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 13:36:13 by vkuikka           #+#    #+#             */
/*   Updated: 2020/08/12 14:31:08 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	ft_error(char *message)
{
	ft_putstr("error: ");
	ft_putstr(message);
	exit(1);
}

void	ft_move(int key, int dir, t_window *window, t_player *player)
{
	double			new_x;
	double			new_y;

	if (key == A_KEY || key == D_KEY)
	{
		new_x = player->pos_x + cos(RAD(player->angle + (90 * dir)))
				* (player->move_speed / 2);
		new_y = player->pos_y + sin(RAD(player->angle + (90 * dir)))
				* (player->move_speed / 2);
	}
	else
	{
		new_x = player->pos_x + ((double)dir * cos(RAD(player->angle)))
				* player->move_speed;
		new_y = player->pos_y + ((double)dir * sin(RAD(player->angle)))
				* player->move_speed;
	}
	if (!window->map[(int)new_y][(int)new_x])
	{
		player->pos_x = new_x;
		player->pos_y = new_y;
	}
}

void	ft_deal_key(int key, t_window *window, t_player *player)
{
	int				dir;

	dir = key == A_KEY || key == S_KEY || key == Q_KEY ? -1 : 1;
	if (key == Q_KEY || key == E_KEY)
	{
		player->angle += dir * player->rot_speed;
		if (player->angle < 0)
			player->angle += 360;
		else if (player->angle > 360)
			player->angle -= 360;
	}
	else
		ft_move(key, dir, window, player);
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
	if (ft_buttons(W_KEY, -1))
		ft_deal_key(W_KEY, window, &window->player);
	if (ft_buttons(A_KEY, -1))
		ft_deal_key(A_KEY, window, &window->player);
	if (ft_buttons(S_KEY, -1))
		ft_deal_key(S_KEY, window, &window->player);
	if (ft_buttons(D_KEY, -1))
		ft_deal_key(D_KEY, window, &window->player);
	if (ft_buttons(NUM1, -1) && window->player.fov > -180)
		window->player.fov--;
	if (ft_buttons(NUM2, -1) && window->player.fov < 180)
		window->player.fov++;
	if (ft_buttons(Q_KEY, -1))
		ft_deal_key(Q_KEY, window, &window->player);
	if (ft_buttons(E_KEY, -1))
		ft_deal_key(E_KEY, window, &window->player);
	SDL_SetRenderDrawColor(window->SDLrenderer, 0, 0, 0, 255);
	SDL_RenderClear(window->SDLrenderer);
	ft_wolf(window->player, window);
	SDL_RenderPresent(window->SDLrenderer);
	return (0);
}
