/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 18:28:42 by vkuikka           #+#    #+#             */
/*   Updated: 2020/08/07 21:29:42 by vkuikka          ###   ########.fr       */
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
		map[i] = ft_strsplit_int(line, ' ');
		i++;
	}
	return (map);
}

int		ft_wall_col(int code)
{
	if (code == 1)	//red
		return (0xff0000);
	if (code == 2)	//yellow
		return (0xff3f00);
	if (code == 3)	//green
		return (0x003f00);
	if (code == 4)	//light blue
		return (0x00ffff);
	if (code == 5)	//blue
		return (0x0000ff);
	if (code == 6)
		return (0xff00ff);
	if (code == 7)
		return (0xffffff);
	return (0x3f3f3f);
}

void	ft_wolf(t_player player, t_window *window)
{
	int		window_x;
	t_ray	ray;

	window_x = 0;
	ray.angle = player.angle - player.fov / 2;

	if (ray.angle < 0)
		ray.angle = 360.0 + ray.angle;
	else if (ray.angle > 360)
		ray.angle = ray.angle - 360.0;

	ray.increment = player.fov / (double)RES_X;
	while (window_x < RES_X)
	{
		ray.x = player.pos_x;
		ray.y = player.pos_y;
		ray.sin = sin(RAD(ray.angle) * 10) / RAY_PREC;	//dont know why *10 but it needed that
		ray.cos = cos(RAD(ray.angle) * 10) / RAY_PREC;
		ray.wall_code = 0;
		while (!ray.wall_code)
		{
			ray.x += ray.cos;
			ray.y += ray.sin;
			ray.wall_code = window->map[(int)(ray.y)][(int)(ray.x)];
		}
		ray.dist = pow(player.pos_x - ray.x, 2) + pow(player.pos_y - ray.y, 2);
		ray.dist = sqrt(ray.dist);
		ray.dist = ray.dist * cos(RAD(ray.angle - player.angle) * 10);
		ft_wolf_line(window_x, (int)((double)RES_Y / ray.dist), window, ft_wall_col(ray.wall_code));
		ray.angle += ray.increment;
		// if (ray.angle < 0)
		// 	ray.angle = 360.0 + ray.angle;
		// else if (ray.angle > 360)
		// 	ray.angle = ray.angle - 360.0;
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
	window->player.angle = 0.0;
	window->player.fov = 45.0;
	window->player.move_speed = 0.1;
	window->player.rot_speed = 1.7;
	window->map = ft_read_map(argc, argv);
	quit = 0;
	while (!quit)
		while (SDL_PollEvent(&event))
			if (event.type == SDL_QUIT || event.key.keysym.scancode == ESC)
				quit = 1;
			else if (event.key.repeat == 0)
			{
				if (event.type == SDL_KEYDOWN || event.type == SDL_MOUSEBUTTONDOWN)
					printf("%d\n", event.key.keysym.scancode);
				else if (event.type == SDL_KEYUP || event.type == SDL_MOUSEBUTTONUP)
					printf("");
					// ft_buttons(event.key.keysym.scancode, 1);
					// ft_buttons(event.key.keysym.scancode, 0);
			}
	return (0);
}
