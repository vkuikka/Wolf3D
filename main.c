#include "wolf.h"


#include <stdio.h>


void	ft_draw_screen(t_wolf player)
{
	float	player_pos[2];


}

int		ft_deal_key(int key, t_mlx *mlx)
{
	t_wolf		player;

	if (key == ESC)
		exit(0);
	printf("%d\n", key);
	player.pos_x = 1;
	player.pos_y = 1;
	if (player.map = ft_read_map(mlx->map_path))
		ft_stop(3);
	ft_draw_screen(player);
	return (0);
}

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

int		main(int argc, char **argv)
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_mlx	*params;
	int		xy[2];

	xy[0] = 1800;
	xy[1] = 1100;
	if (!(params = (t_mlx *)malloc(sizeof(t_mlx))))
		ft_stop(0);
	if (argc != 2)
		ft_stop(3);
	if (!(mlx_ptr = mlx_init()))
		ft_stop(1);
	if (!(win_ptr = mlx_new_window(mlx_ptr, xy[0], xy[1], "fdf")))
		ft_stop(1);
	mlx_key_hook(win_ptr, ft_deal_key, (void*)params);
	mlx_loop(mlx_ptr);
	(void)argv;
	return (0);
}
