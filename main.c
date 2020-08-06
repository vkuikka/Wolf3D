#include "wolf.h"

#include "libft/includes/libft.h"

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
	return (0x3f3f3f);
}


void	ft_wolf(t_wolf player, t_window *window, int key)
{
// 	int		map[24][24] = {
//   {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
//   {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,7},
//   {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
//   {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
//   {4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,7},
//   {4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,1,1,0,7,7,7,7,7},
//   {4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
//   {4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
//   {4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
//   {4,0,1,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
//   {4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
//   {4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
//   {6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
//   {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
//   {6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
//   {4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
//   {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
//   {4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
//   {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
//   {4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
//   {4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
//   {4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
//   {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
//   {4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
// };
	int		map[5][5] = {
		{1,1,1,1,1},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{1,1,1,1,1}
	};
	int color;
	int	wx;

	color = 0x3f3f3f;
	wx = 0;
	double	ray_angle;
	double	ray_increment;
	double	ray_x;
	double	ray_y;
	double	ray_sin;
	double	ray_cos;
	double	dist;

	int		hit = 0;


	ray_angle = player.angle - player.fov / 2;

	if (ray_angle < 0)
		ray_angle = 360.0 + ray_angle;
	else if (ray_angle > 360)
		ray_angle = ray_angle - 360.0;

	ray_increment = player.fov / RES_X;

	// printf("%f\n", ray_angle);
	while (wx < RES_X)
	{
		ray_x = player.pos_x;
		ray_y = player.pos_y;
		ray_sin = sin(RAD(ray_angle) * 10) / RAY_PREC;
		ray_cos = cos(RAD(ray_angle) * 10) / RAY_PREC;
		hit = 0;
		while (!hit)
		{
			ray_x += ray_cos;
			ray_y += ray_sin;
			hit = map[(int)floor(ray_y)][(int)floor(ray_x)];
		}
		dist = pow(player.pos_x - ray_x, 2) + pow(player.pos_y - ray_y, 2);
		dist = sqrt(dist);
		// if (wx == RES_X / 2)
		// {
		// 	printf("sin: %f\n", ray_sin);
		// 	printf("cos: %f\n", ray_cos);

		// 	printf("pos x: %f\n", player.pos_x);
		// 	printf("pos y: %f\n", player.pos_y);

		// 	printf("ray x: %f\n", ray_x);
		// 	printf("ray y: %f\n", ray_y);

		// 	printf("pow x: %f\n", pow(player.pos_x - ray_x, 2));
		// 	printf("pow y: %f\n", pow(player.pos_y - ray_y, 2));

		// 	printf("dist: %f\n\n", dist);
		// }
		// color = ft_wall_col(hit);
		ft_wolf_line(wx, (int)((double)RES_Y / (double)dist), window, color);
		ray_angle += ray_increment;
		if (ray_angle < 0)
			ray_angle = 360.0 + ray_angle;
		else if (ray_angle > 360)
			ray_angle = ray_angle - 360.0;
		wx++;
	}

	//dist = diff_x * cos(player.dir * PI / 180) + diff_y * sin(player.dir * PI / 180);

	return ;
	(void)player;
	(void)window;
	(void)key;
	(void)map;
}

int		ft_deal_key(int key, t_window *window)
{
	static t_wolf	*player = NULL;
	double	new_x;
	double	new_y;

	if (key == ESC)
		exit(0);
	// printf("%d\n", key);
	// return (0);
	if (!player)
	{
		if (!(player = (t_wolf *)malloc(sizeof(t_wolf))))
			ft_stop(0);
		player->pos_x = 1.0;
		player->pos_y = 1.0;
		player->angle = 0.0;
		player->fov = 30.0;
		player->move_speed = 0.6;
		player->rot_speed = 2.0;
	}
	if (key == TURN_LEFT)
		player->angle -= player->rot_speed;
	if (key == TURN_RIGHT)
		player->angle += player->rot_speed;


	if (key == LEFT)
		player->angle -= player->rot_speed;
	if (key == RIGHT)
		player->angle += player->rot_speed;

	double		tmpx;
	double		tmpy;

	if (player->angle < 0)
		player->angle = player->angle + 360;
	if (player->angle > 360)
		player->angle = player->angle - 360;

	if (key == UP)
	{
		tmpx = cos(RAD(player->angle) * 10) * player->move_speed;
		tmpy = sin(RAD(player->angle) * 10) * player->move_speed;
		new_x = player->pos_x + tmpx;
		new_y = player->pos_y + tmpy;
		player->pos_x = new_x;
		player->pos_y = new_y;
	}
	if (key == DOWN)
	{
		tmpx = cos(RAD(player->angle) * 10) * player->move_speed;
		tmpy = sin(RAD(player->angle) * 10) * player->move_speed;
		new_x = player->pos_x - tmpx;
		new_y = player->pos_y - tmpy;
		player->pos_x = new_x;
		player->pos_y = new_y;
	}

	// printf("angle%f\n", player->angle);
	// printf("x%f\n", new_x);
	// printf("y%f\n", new_y);
	// printf("x+%f\n", tmpx);
	// printf("y+%f\n\n", tmpy * -1);

	// if (player.map = ft_read_map(mlx->map_path))
	// 	ft_stop(3);

	ft_clear(window);
	ft_wolf(*player, window, key);
	ft_draw_window(window);
	return (0);
}

int		main(int argc, char **argv)
{
	t_window	*window;
	int			xy[2];

	xy[0] = RES_X;
	xy[1] = RES_Y;
	if (!(window = (t_window *)malloc(sizeof(t_window))))
		ft_stop(0);
	window->pixel_col = NULL;
	if (argc != 2)
		ft_stop(3);
	if (!(window->mlx_ptr = mlx_init()))
		ft_stop(1);
	if (!(window->win_ptr = mlx_new_window(window->mlx_ptr, xy[0], xy[1], "WOLF")))
		ft_stop(1);
	// mlx_key_hook(window->win_ptr, ft_deal_key, (void*)window);
	mlx_hook(window->win_ptr, 2, 1, ft_deal_key, (void*)window);
	mlx_loop(window->mlx_ptr);
	return (0);
	(void)argv;
}
