/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 17:52:58 by vkuikka           #+#    #+#             */
/*   Updated: 2020/08/08 16:17:04 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

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
	SDL_SetRenderDrawColor(window->SDLrenderer, 0, 0, 0, 255);
	SDL_RenderClear(window->SDLrenderer);
}

void		ft_wolf_line(int x, int len, t_window *window, unsigned color)
{
	int		y;
	int		limit;

	SDL_SetRenderDrawColor(window->SDLrenderer,
		R_VAL(color), G_VAL(color), B_VAL(color), 255);
	if (len > RES_Y)
		len = RES_Y;
	y = RES_Y / 2 - len / 2;
	limit = RES_Y / 2 + len / 2;
	while (y < limit)
	{
		SDL_RenderDrawPoint(window->SDLrenderer, x, y);
		// ft_pixel(x, y, color, window);
		y++;;
	}
}