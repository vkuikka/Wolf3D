/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 17:52:58 by vkuikka           #+#    #+#             */
/*   Updated: 2020/08/07 21:16:32 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

#include <stdio.h>

void		ft_pixel(int x, int y, int color, t_window *window)
{
	SDL_RenderDrawPoint(window->SDLrenderer, x, y);
}

void		ft_draw_window(t_window *window)
{
	SDL_RenderPresent(window->SDLrenderer);
}

void		ft_clear(t_window *window)
{
	SDL_RenderClear(window->SDLrenderer);
	for (int x = 0; x < RES_X; x++)
		for (int y = 0; y < RES_Y; y++)
			SDL_RenderDrawPoint(window->SDLrenderer, x, y);
}

void		ft_wolf_line(int x, int len, t_window *window, unsigned color)
{
	int		y;
	int		limit;

	if (len > RES_Y)
		len = RES_Y;
	y = RES_Y / 2 - len / 2;
	limit = RES_Y / 2 + len / 2;
	while (y < limit)
	{
		ft_pixel(x, y, color, window);
		y++;;
	}
}