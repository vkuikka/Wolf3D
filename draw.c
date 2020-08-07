/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 17:52:58 by vkuikka           #+#    #+#             */
/*   Updated: 2020/08/07 18:26:09 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

#include <stdio.h>

void		ft_pixel(int x, int y, int color, t_window *window)
{
	int			spot;

	if (x >= 0 && y >= 0 && x < RES_X && y < RES_Y)
	{
		spot = y * window->size_of_line + x * 4;
		window->pixel_col[spot] = (unsigned char)B_VAL(color);
		window->pixel_col[spot + 1] = (unsigned char)G_VAL(color);
		window->pixel_col[spot + 2] = (unsigned char)R_VAL(color);
		window->pixel_col[spot + 3] = 0;
	}
}

void		ft_draw_window(t_window *window)
{
	mlx_put_image_to_window(window->mlx_ptr, window->win_ptr, window->image, 0, 0);
}

void		ft_clear(t_window *window)
{
	int		x;
	int		y;
	int		spot;

	x = 0;
	y = 0;
	if (!window->pixel_col)
	{
		if (!(window->image = mlx_new_image(window->mlx_ptr, RES_X, RES_Y)))
			exit(1);
		window->pixel_col = mlx_get_data_addr(window->image, &window->bits_per_pixel, &window->size_of_line, &window->endian);
	}
	while (y < RES_Y)
	{
		x = 0;
		while (x < RES_X)
		{
			spot = y * window->size_of_line + x * 4;
			window->pixel_col[spot] = 0;
			window->pixel_col[spot + 1] = 0;
			window->pixel_col[spot + 2] = 0;
			window->pixel_col[spot + 3] = 0;
			x++;
		}
		y++;
	}
}

void		ft_wolf_line(int x, int len, t_window *window, unsigned c)
{
	int		y;
	int		limit;

	if (len > RES_Y)
		len = RES_Y;
	y = RES_Y / 2 - len / 2;
	limit = RES_Y / 2 + len / 2;
	while (y < limit)
	{
		ft_pixel(x, y, c, window);
		y++;;
	}
}