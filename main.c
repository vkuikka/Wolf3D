/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 18:28:42 by vkuikka           #+#    #+#             */
/*   Updated: 2020/08/08 16:19:37 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

#include "libft/includes/libft.h"

#include <stdio.h>

int		**ft_read_map(int argc, char **argv)
{
	char	*line;
	int		**map;
	int		has_zero;
	int		fd;
	int		i;

	i = 0;
	map = NULL;
	has_zero = 0;
	if (argc != 2)
		ft_error("give one map file name as argument\n");
	if (1 > (fd = open(argv[1], O_RDONLY)))
		ft_error("failed to open given file\n");
	while (0 < get_next_line(fd, &line))
		i++;
	if (!(map = (int **)malloc(sizeof(int *) * i)))
		return (NULL);
	close(fd);
	if (1 > (fd = open(argv[1], O_RDONLY)))
		ft_error("failed to open given file\n");
	i = 0;
	while (0 < get_next_line(fd, &line))
	{
		if (line[ft_strlen(line) - 1] == '0' || line[0] == '0' ||
			line[ft_strlen(line) - 1] == ' ' || line[0] == ' ')
			ft_error("given file is not valid\n");
		if (!(map[i] = (int *)malloc(sizeof(int) * ft_word_count(line, ' '))))
			return (NULL);
		map[i++] = ft_strsplit_int(line, ' ');
	}
	return (map);
}

int		ft_wall_col(t_ray ray)
{
	static int	prev_color = 0;
	int			color;
	
	color = 0;
	if ((int)ray.prev_x != (int)ray.x && (int)ray.prev_y != (int)ray.y)
		color = prev_color;
	else if ((int)ray.prev_x > (int)ray.x)
		color = 0xff0000;
	else if ((int)ray.prev_y > (int)ray.y)
		color = 0x003f00;
	else if ((int)ray.prev_x < (int)ray.x)
		color = 0x00ffff;
	else if ((int)ray.prev_y < (int)ray.y)
		color = 0x0000ff;
	prev_color = color;
	return (color);
}

void	ft_wolf(t_player player, t_window *window)
{
	t_ray	ray;
	int		window_x;

	window_x = 0;
	if (player.angle < 0)
		player.angle += 360;
	else if (player.angle > 360)
		player.angle -= 360;
	ray.angle = player.angle - player.fov / 2;
	ray.increment = player.fov / (double)RES_X;
	while (window_x < RES_X)
	{
		ray.x = player.pos_x;
		ray.y = player.pos_y;
		ray.sin = sin(RAD(ray.angle)) / RAY_PREC;
		ray.cos = cos(RAD(ray.angle)) / RAY_PREC;
		ray.wall_code = 0;
		while (!ray.wall_code)
		{
			ray.prev_x = ray.x;
			ray.prev_y = ray.y;
			ray.x += ray.cos;
			ray.y += ray.sin;
			ray.wall_code = window->map[(int)(ray.y)][(int)(ray.x)];
		}
		ray.dist = sqrt(pow(player.pos_x - ray.x, 2) + pow(player.pos_y - ray.y, 2)) * cos(RAD(ray.angle - player.angle));
		// ray.dist = sqrt(ray.dist);
		// ray.dist = ray.dist * cos(RAD(ray.angle - player.angle));
		// if (window_x == RES_X / 2)
		// 	printf("%f\n", ray.angle);
		ft_wolf_line(window_x, (int)((double)RES_Y / ray.dist), window, ft_wall_col(ray));
		ray.angle += ray.increment;
		window_x++;
	}
	return ;
}

int		main(int argc, char **argv)
{
	SDL_Event	event;
	t_window	*window;
	int			quit;

	if (!(window = (t_window *)malloc(sizeof(t_window))))
		ft_error("memory allocation failed\n");
	if (SDL_Init(SDL_INIT_EVERYTHING))
	{
		printf("%s\n", SDL_GetError());
		ft_error("could not initialize SDL\n");
	}
	window->SDLwindow = SDL_CreateWindow("WOLF", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, RES_X, RES_Y, 0);
	window->SDLrenderer	= SDL_CreateRenderer(window->SDLwindow, -1, 0);
	window->player.pos_x = 1.5;
	window->player.pos_y = 1.5;
	window->player.angle = 0;
	window->player.fov = 45.0;
	window->player.move_speed = 0.1;
	window->player.rot_speed = 2;
	window->map = ft_read_map(argc, argv);
	quit = 0;
	while (!quit)
	{
		while (SDL_PollEvent(&event))
			if (event.type == SDL_QUIT || event.key.keysym.scancode == ESC)
				quit = 1;
			else if (event.key.repeat == 0)
			{
				if (event.type == SDL_KEYDOWN)
				{
					ft_buttons(event.key.keysym.scancode, 1);
				}
				else if (event.type == SDL_KEYUP)
					ft_buttons(event.key.keysym.scancode, 0);
				else if (event.type == SDL_MOUSEBUTTONDOWN)
					window->map = ft_read_map(argc, argv);
			}
					ft_loop(window);
		// if (ft_buttons(-1, -1))
	}
	return (0);
}
