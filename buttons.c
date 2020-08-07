/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 13:36:13 by vkuikka           #+#    #+#             */
/*   Updated: 2020/08/07 21:16:52 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"


#include <stdio.h>


void	ft_error(char *message)
{
	ft_putstr(message);
	exit(1);
}

// int		ft_deal_key(int key, t_window *window, t_player *player)
// {
// 	double			new_x;
// 	double			new_y;
// 	int				dir;

// 	new_x = 1.5;
// 	new_y = 1.5;
// 	dir = 1;
// 	if (key == ESC)
// 		exit(1);
// 	if (key == A_KEY || key == S_KEY || key == Q_KEY)
// 		dir = -1;
// 	if (key == Q_KEY || key == E_KEY)
// 	{
// 		player->angle += dir * player->rot_speed;
// 		if (player->angle < 0)
// 			player->angle = player->angle + 360;
// 		else if (player->angle > 360)
// 			player->angle = player->angle - 360;
// 		window->player = *player;
// 		return (0);
// 	}
// 	else if (key == A_KEY || key == D_KEY)
// 	{
// 		new_x = player->pos_x + cos(RAD(player->angle + (90 * dir)) * 10) * (player->move_speed / 2);
// 		new_y = player->pos_y + sin(RAD(player->angle + (90 * dir)) * 10) * (player->move_speed / 2);
// 	}
// 	else if (key == W_KEY || key == S_KEY)
// 	{
// 		new_x = player->pos_x + ((double)dir * cos(RAD(player->angle) * 10)) * player->move_speed;
// 		new_y = player->pos_y + ((double)dir * sin(RAD(player->angle) * 10)) * player->move_speed;
// 	}
// 	if (!window->map[(int)new_y][(int)new_x])
// 	{
// 		player->pos_x = new_x;
// 		player->pos_y = new_y;
// 	}
// 	window->player = *player;
// 	return (0);
// }

// int		ft_buttons(int button, void *checking)
// {
// 	static int		*keys;
// 	int				i;
// 	int				empty_found;

// 	empty_found = 0;
// 	if (!(keys))
// 	{
// 		if (!(keys = (int *)malloc(sizeof(int) * SAME_TIME_BUTTONS)))
// 			ft_error("memory allocation failed\n");
// 		i = -1;
// 		while (++i < SAME_TIME_BUTTONS)
// 			keys[i] = -1;
// 	}
// 	i = -1;
// 	while (++i < SAME_TIME_BUTTONS)
// 	{
// 		if (checking && keys[i] == button)
// 			return (1);
// 		else if (!checking && keys[i] == button)
// 		{
// 			// printf("relesed %d\n", button);
// 			keys[i] = -1;
// 			return (0);
// 		}
// 		if (keys[i] == -1)
// 			empty_found = 1;
// 	}
// 	if (empty_found && !checking && i == SAME_TIME_BUTTONS && (i = -1))
// 	{
// 		while (++i < SAME_TIME_BUTTONS)
// 			if (keys[i] == -1)
// 			{
// 				// printf("pressed %d\n", button);
// 				keys[i] = button;
// 				return (0);
// 			}
// 	}
// 	return (0);
// }

// int		ft_loop(t_window *window)
// {
// 	int		i;

// 	i = 0;
// 	// if (ft_buttons(W_KEY, window))
// 	if (ft_buttons(ARROW_U, window))
// 		ft_deal_key(W_KEY, window, &window->player);
// 	if (ft_buttons(A_KEY, window))
// 		ft_deal_key(A_KEY, window, &window->player);
// 	if (ft_buttons(S_KEY, window))
// 		ft_deal_key(S_KEY, window, &window->player);
// 	if (ft_buttons(D_KEY, window))
// 		ft_deal_key(D_KEY, window, &window->player);
// 	// if (ft_buttons(ARROW_U, window))
// 	// 	ft_deal_key(ARROW_U, window, &window->player);
// 	// if (ft_buttons(ARROW_D, window))
// 	// 	ft_deal_key(ARROW_D, window, &window->player);
// 	if (ft_buttons(ARROW_L, window))
// 		window->player.fov--;
// 	if (ft_buttons(ARROW_R, window))
// 		window->player.fov++;
// 	if (ft_buttons(Q_KEY, window))
// 		ft_deal_key(Q_KEY, window, &window->player);
// 	if (ft_buttons(E_KEY, window))
// 		ft_deal_key(E_KEY, window, &window->player);
// 	if (ft_buttons(ESC, window))
// 		ft_deal_key(ESC, window, &window->player);
// 	ft_clear(window);
// 	ft_wolf(window->player, window);
// 	for (int y = 0; y < RES_Y; y++)
// 		ft_pixel(RES_X / 2, y, 0x0000ff, window);
// 	ft_draw_window(window);
// 	return (0);
// }
