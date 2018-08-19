/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldehaudt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 04:32:46 by ldehaudt          #+#    #+#             */
/*   Updated: 2018/06/23 04:32:47 by ldehaudt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod1.h"

void	set_color(void)
{
	int i;

	i = 0;
	while (i < 256)
	{
		g_lcolor[i] = t_color((float)i / 255.0, g_color.c1, g_color.c2);
		i++;
	}
}

float	get_h(t_pt p, t_vars *vp)
{
	int		x;
	int		y;

	x = (int)((p.fx + 1) * D);
	y = (int)((p.fy + 1) * D);
	return (vp->height[y][x]);
}

void	init_plane(t_vars *vp)
{
	int i;
	int j;

	set_height(vp);
	vp->pl = (t_2d**)malloc(sizeof(t_2d*) * ((D >> 4) + 1));
	i = 0;
	while (i <= D >> 4)
	{
		vp->pl[i] = (t_2d*)malloc(sizeof(t_2d) * ((D >> 4) + 1));
		j = 0;
		while (j <= D >> 4)
		{
			vp->pl[i][j].wet = 0;
			vp->pl[i][j].lvl = (unsigned char)((vp->height[i << 5][j << 5] + 1)
			* 120);
			j++;
		}
		i++;
	}
	make_landscape(vp);
}

void	loops(t_vars vars)
{
	mlx_hook(vars.win, 2, 0, &k_control, (void*)(&vars));
	mlx_loop_hook(vars.mlx, &refresh, (void*)(&vars));
	mlx_loop(vars.mlx);
}

int		main(int ac, char **av)
{
	t_vars	vars;
	int		db;

	if (ac != 2)
		return (ft_printf("{O}Invalid Number of Arguments\n"));
	if (read_map(&vars, av[1]) == false)
		return (-1);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, W, H, "mod1");
	vars.img = mlx_new_image(vars.mlx, W, H);
	vars.str = mlx_get_data_addr(vars.img, &db, &db, &db);
	vars.landscape = ft_strnew(sizeof(unsigned int) * (W * H + 1));
	vars.pix = (t_pixel*)malloc(sizeof(t_pixel) * (W * H + 1));
	vars.mode = 1;
	vars.go = 1;
	vars.rot.fx = 3 * PI / 20;
	vars.rot.fz = 3 * PI / 20;
	g_lvl = 0;
	g_color.c1 = 0x006324;
	g_color.c2 = 0x8ed64f;
	init_plane(&vars);
	refresh(&vars);
	set_random();
	loops(vars);
	return (0);
}
