/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 18:28:42 by vkuikka           #+#    #+#             */
/*   Updated: 2020/08/16 15:04:09 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	ft_read_map(int fd, t_window *window)
{
	size_t	len;
	char	*line;
	int		has_zero;
	int		err;
	int		i;

	i = 0;
	len = 0;
	while (0 < (err = get_next_line(fd, &line)))
	{
		if (len && len != ft_strlen(line))
			ft_error("given file is not valid\n");
		len = ft_strlen(line);
		has_zero = ft_strstr(line, " 0 ") ? 1 : 0;
		if ((has_zero && i == 0) ||
			line[len - 1] == '0' || line[0] == '0' ||
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

int			ft_choose_color(t_ray ray)
{
	static int		prev_color = 0;
	int				color;

	color = 0;
	if ((int)ray.prev_x != (int)ray.x && (int)ray.prev_y != (int)ray.y)
		color = prev_color;
	else if ((int)ray.prev_x > (int)ray.x)
		color = 0;
	else if ((int)ray.prev_y > (int)ray.y)
		color = 1;
	else if ((int)ray.prev_x < (int)ray.x)
		color = 2;
	else if ((int)ray.prev_y < (int)ray.y)
		color = 3;
	prev_color = color;
	return (color);
}

void		ft_draw_line(int screen_x, int len, t_window *window, t_ray ray)
{
	SDL_Color	col;
	int			limit;
	int			screen_y;
	double		imgx;
	double		imgy;

	imgx = 0;
	imgy = 0;
	screen_y = 0;
	col.a = ft_choose_color(ray);
	imgx = fmod(col.a == 0 || col.a == 2 ? ray.y : ray.x, 1) *
				window->textures[col.a]->w;
	imgy = 0;
	limit = RES_Y / 2 + len / 2;
	screen_y = RES_Y / 2 - (len > RES_Y ? RES_Y : len) / 2;
	while (screen_y < limit && screen_y < RES_Y)
	{
		imgy = ((double)screen_y - (RES_Y / 2 - len / 2)) /
				((double)limit - (RES_Y / 2 - len / 2));
		SDL_GetRGB(ft_get_pixel(window->textures[col.a], imgx,
			imgy * window->textures[col.a]->h),
			window->textures[col.a]->format, &col.r, &col.g, &col.b);
		SDL_SetRenderDrawColor(window->SDLrenderer, col.r, col.g, col.b, 255);
		SDL_RenderDrawPoint(window->SDLrenderer, screen_x, screen_y++);
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
	window->player.fov = 61.0;
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

	if (SDL_Init(SDL_INIT_EVERYTHING) || !IMG_Init(IMG_INIT_PNG))
		ft_error("could not initialize SDL\n");
	if (!(window = (t_window *)malloc(sizeof(t_window))) ||
		!(window->textures = (SDL_Surface **)malloc(sizeof(SDL_Surface *) * 4)))
		ft_error("memory allocation failed\n");
	if (!(window->textures[0] = IMG_Load(TEXTURE_1)) ||
		!(window->textures[1] = IMG_Load(TEXTURE_2)) ||
		!(window->textures[2] = IMG_Load(TEXTURE_3)) ||
		!(window->textures[3] = IMG_Load(TEXTURE_4)))
		ft_error("could not find texture\n");
	ft_init(window, argc, argv);
	while (1)
	{
		while (SDL_PollEvent(&event))
			if (event.type == SDL_QUIT || event.key.keysym.scancode == ESC)
				return (0);
			else if (event.key.repeat == 0 && event.type == SDL_KEYDOWN)
				ft_buttons(event.key.keysym.scancode, 1);
			else if (event.key.repeat == 0 && event.type == SDL_KEYUP)
				ft_buttons(event.key.keysym.scancode, 0);
		ft_loop(window);
	}
}
