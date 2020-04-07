#include "wolf.h"


#include <stdio.h>


int		ft_stop(int code)
{
	ft_putstr("error: ");
	if (code == 0)
		ft_putstr("memory allocation error\n");
	if (code == 1)
		ft_putstr("failed to open new window\n");
	if (code == 2)
		ft_putstr("failed to create image to window\n");
	if (code == 3)
		ft_putstr("give valid file as argument\n");
	exit(1);
}

void	ft_draw_line(int x, int len, t_mlx mlx, unsigned c)
{
	int		y;
	int		limit;

	if (len > 1100)
	{
		len = 1100;
		c = 0xff0000;
	}
	y = RES_Y / 2 - len / 2;
	limit = RES_Y / 2 + len / 2;
	while (y < limit)
	{
		mlx_pixel_put(mlx.mlx_ptr, mlx.win_ptr, x, y, c);
		y++;;
	}
}

void	ft_draw_screen(t_wolf player, t_mlx mlx, int key)
{
	int		map[5][5] = {
		{2,2,2,2,2},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{2,2,2,2,2}
	};
	double	vx = 1;
	double	vy = 1;
	(void)key;

	double	step_y = 0;
	double	step_x = 0;

	double	diff_y = 0;
	double	diff_x = 0;

	double	line_len = 0;
	double	dist = 0;

	double	xIntercept = 0;
	double	yIntercept = 0;

	double x = 0;

	int color = 0xffffff;

	while (x++ < 1800)
	{
		diff_x = (1 - player.sub_pos_x) * tan(player.dir * PI / 180);
		diff_y = player.sub_pos_y / tan(player.dir * PI / 180);

		step_x = tan(player.dir * PI / 180);
		step_y = 1 / tan(player.dir * PI / 180);

		xIntercept = player.pos_x + player.sub_pos_x + -player.sub_pos_y / tan(player.dir * PI / 180);
		yIntercept = player.pos_y + player.sub_pos_y + player.sub_pos_x / tan(player.dir * PI / 180);

		vx = (double)player.pos_x + player.sub_pos_x;
		vy = (double)player.pos_y + player.sub_pos_y;
		if (x == 1800 / 2)
			printf("\nvx: %f\nvy: %f", vx, vy);

		int nohit = 1;
		while (nohit)
		{
			while (yIntercept < vy)
			{
				if (map[player.pos_x][(int)yIntercept])
				{
					nohit = 0;
					break;
				}
				vx += 1.0;
				yIntercept += step_y;
			}
			while (xIntercept < vx && nohit)
			{
				if (map[(int)xIntercept][player.pos_y])
				{
					nohit = 0;
					break;
				}
				vy -= 1.0;
				xIntercept += step_x;
			}
		}
		vx -= player.pos_x;
		vy -= player.pos_y;
		dist = vx * cos(player.dir * PI / 180) + vy * sin(player.dir * PI / 180);
		if (x == 1800 / 2)
		{
			printf("\nxinter: %f\nyinter: %f", xIntercept, yIntercept);
			printf("\nposx: %d\nposy: %d\ndir: %f\nstepx: %f\nstepy: %f\n", player.pos_x, player.pos_y, player.dir, step_x, step_y);
			printf("diff_x: %f\ndiff_y: %f\ndist: %f\n", diff_x, diff_y, dist);
		}
		line_len = 1100 / dist;
		ft_draw_line(x, line_len, mlx, color);
		player.dir += (double)45 / 1800;
	}
}


	// while (x++ < 1800)
	// {
	// 	diff_x = -(1 - player.sub_pos_x) * tan(player.dir * PI / 180);
	// 	diff_y = player.sub_pos_y / tan(player.dir * PI / 180);

	// 	step_x = -tan(player.dir * PI / 180);
	// 	step_y = 1 / tan(player.dir * PI / 180);

	// 	vx = (double)player.pos_x + player.sub_pos_x - 1;
	// 	vy = (double)player.pos_y + player.sub_pos_y - 1;

	// 	if (step_x < 0)
	// 		step_x *= -1;
	// 	if (step_y < 0)
	// 		step_y *= -1;
	// 	nohit = 1;
	// 	while (nohit)
	// 	{
	// 		if (step_x > step_y)
	// 		{
	// 			vx += step_x * step_y;
	// 			vy += step_y;
	// 		}
	// 		else
	// 		{
	// 			vx += step_x;
	// 			vy += step_y * step_x;
	// 		}
	// 		if (vx > 5 || vy > 5)
	// 		{
	// 			color = 0x0000ff;
	// 			nohit = 0;
	// 		}
	// 		else if (map[(int)vy][(int)vx] == 2)
	// 		{
	// 			color = 0xff0000;
	// 			nohit = 0;
	// 		}
	// 		else if (map[(int)vy][(int)vx] == 1)
	// 		{
	// 			color = 0x00ff00;
	// 			nohit = 0;
	// 		}
	// 		else if (map[(int)vy][(int)vx] == 3)
	// 		{
	// 			color = 0xffff00;
	// 			nohit = 0;
	// 		}
	// 	}
	// 	diff_x += vx * step_x;
	// 	diff_y += vy * step_y;

	// 	dist = diff_x * cos(player.dir * PI / 180) + diff_y * sin(player.dir * PI / 180);
	// 	if (x == 1800 / 2)
	// 	{
	// 		printf("\nposx: %d\nposy: %d\ndir: %f\nstepx: %f\nstepy: %f\n", player.pos_x, player.pos_y, player.dir, step_x, step_y);
	// 		printf("diff_x: %f\ndiff_y: %f\ndist: %f\n", diff_x, diff_y, dist);
	// 	}
	// 	line_len = 1100 / dist;
	// 	ft_draw_line(x, line_len, mlx, color);
	// 	player.dir -= (double)20 / 1800;
	// }
// }

// int		ft_cast(int angle, int x,  t_wolf player)
// {
// 	double	cam;
// 	double	ray_x;
// 	double	ray_y;
// 	double	ray_dirx;
// 	double	ray_diry;
// 	double	mapx;
// 	double	mapy;

// 	cam  = 2 * x / (double)RES_X - 1;
// 	ray_x = player.pos_x;
// }

// void	ft_render(t_wolf player, t_mlx mlx, int key)
// {
// 	int		x;
// 	int		column;
// 	double	ray_angle;

// 	x = 0;
// 	while (x < RES_X)
// 	{
// 		if (x < RES_X / 2)
// 			ray_angle = player.dir - (RES_X / 20 * x);
// 		else
// 			ray_angle = player.dir + (RES_X / 20 * x);
// 		column = ft_cast(ray_angle, x, player);
// 		ft_draw_line(x, column, mlx, 0xffffff - column);
// 		x++;
// 	}
// }

int		ft_deal_key(int key, t_mlx *mlx)
{
	static t_wolf	*player = NULL;

	if (key == ESC)
		exit(0);
	// printf("%d\n", key);
	// return (0);
	if (!player)
	{
		if (!(player = (t_wolf *)malloc(sizeof(t_wolf))))
			ft_stop(0);
		player->pos_x = 1;
		player->pos_y = 1;
		player->sub_pos_x = 0.5;
		player->sub_pos_y = 0.5;
		player->dir = 20;
	}
	if (key == 97)
		player->dir++;
	if (key == 100)
		player->dir--;
	if (player->dir < 0)
		player->dir = 360 + player->dir;

	if (key == 65361)
		player->pos_x--;
	if (key == 65363)
		player->pos_x++;
	if (key == 65362)
		player->pos_y--;
	if (key == 65364)
		player->pos_y++;
	// if (player.map = ft_read_map(mlx->map_path))
	// 	ft_stop(3);
	mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
	ft_draw_screen(*player, *mlx, key);
	return (0);
}



int		main(int argc, char **argv)
{
	t_mlx	*params;
	int		xy[2];

	xy[0] = 1800;
	xy[1] = 1100;
	if (!(params = (t_mlx *)malloc(sizeof(t_mlx))))
		ft_stop(0);
	if (argc != 2)
		ft_stop(3);
	if (!(params->mlx_ptr = mlx_init()))
		ft_stop(1);
	if (!(params->win_ptr = mlx_new_window(params->mlx_ptr, xy[0], xy[1], "fdf")))
		ft_stop(1);
	// mlx_key_hook(params->win_ptr, ft_deal_key, (void*)params);
	mlx_hook(params->win_ptr, 2, 1, ft_deal_key, (void*)params);
	mlx_loop(params->mlx_ptr);
	(void)argv;
	return (0);
}
