/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 18:28:42 by vkuikka           #+#    #+#             */
/*   Updated: 2020/08/12 14:31:25 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

#include <stdio.h>

static void	ft_read_map(int fd, t_window *window)
{
	size_t	len;
	char	*line;
	int		has_zero;
	int		err;
	int		i;

	i = 0;
	while (0 < (err = get_next_line(fd, &line)))
	{
		if (len && len != ft_strlen(line))
			ft_error("given file is not valid\n");
		len = ft_strlen(line);
		has_zero = ft_strstr(line, " 0 ") ? 1 : 0;
		if (has_zero && i == 0)
			ft_error("given file is not valid\n");
		if (line[len - 1] == '0' || line[0] == '0' ||
			line[len - 1] == ' ' || line[0] == ' ')
			ft_error("given file is not valid\n");
		else
			!(window->map[i++] = ft_strsplit_int(line, ' ')) ?
				ft_error("memory allocation failed\n") : free(line);
	}
	if (has_zero)
		ft_error("given file is not valid\n");
	err < 0 || close(fd) ? ft_error("failed to read given file\n") : free(line);
}

void		ft_draw_line(int x, int len, t_window *window, t_ray ray)
{
	static int	prev_color = 0;
	int			color;
	int			limit;
	int			y;

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
	SDL_SetRenderDrawColor(window->SDLrenderer,
		R_VAL(color), G_VAL(color), B_VAL(color), 255);
	if (len > RES_Y)
		len = RES_Y;
	y = RES_Y / 2 - len / 2;
	limit = RES_Y / 2 + len / 2;
	while (y < limit)
		SDL_RenderDrawPoint(window->SDLrenderer, x, y++);
}

void		ft_wolf(t_player player, t_window *window)
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
		ray.wall_code = 0;
		while (!(ray.wall_code = window->map[(int)(ray.y)][(int)(ray.x)]))
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

static void	ft_init(t_window *window, int argc, char **argv)
{
	int			err;
	int			fd;
	int			i;

	i = 0;
	if (!(window->SDLwindow = SDL_CreateWindow("WOLF", SDL_WINDOWPOS_CENTERED,
						SDL_WINDOWPOS_CENTERED, RES_X, RES_Y, 0)))
		ft_error("could not create window");
	if (!(window->SDLrenderer = SDL_CreateRenderer(window->SDLwindow, -1, 0)))
		ft_error("could not create renderer");
	window->player.pos_x = 1.5;
	window->player.pos_y = 1.5;
	window->player.angle = 0;
	window->player.fov = 45.0;
	window->player.move_speed = 0.1;
	window->player.rot_speed = 2;
	if (1 > (fd = open(argc == 2 ? argv[1] : NULL, O_RDONLY)))
		ft_error("give one valid map file name as argument\n");
	while (0 < (err = get_next_line(fd, &argv[0])) && ++i)
		free(argv[0]);
	free(argv[0]);
	if (!(window->map = (int **)malloc(sizeof(int *) * i)) || err < 0 ||
			close(fd) || 1 > (fd = open(argv[1], O_RDONLY)))
		ft_error("failed to allocate memory and read file\n");
	ft_read_map(fd, window);
}

int			main(int argc, char **argv)
{
	SDL_Event	event;
	t_window	*window;
	int			quit;

	if (SDL_Init(SDL_INIT_EVERYTHING))
		ft_error("could not initialize SDL\n");
	if (!(window = (t_window *)malloc(sizeof(t_window))))
		ft_error("memory allocation failed\n");
	ft_init(window, argc, argv);
	quit = 0;
	while (!quit)
	{
		while (SDL_PollEvent(&event))
			if (event.type == SDL_QUIT || event.key.keysym.scancode == ESC)
				quit = 1;
			else if (event.key.repeat == 0)
			{
				if (event.type == SDL_KEYDOWN)
					ft_buttons(event.key.keysym.scancode, 1);
				else if (event.type == SDL_KEYUP)
					ft_buttons(event.key.keysym.scancode, 0);
			}
		ft_loop(window);
	}
	return (0);
}
