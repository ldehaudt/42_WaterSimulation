/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldehaudt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 06:57:57 by ldehaudt          #+#    #+#             */
/*   Updated: 2018/06/23 06:58:00 by ldehaudt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod1.h"

float	random1(void)
{
	static int	n = 751;

	n = n * n % (97 * 7703);
	return ((float)(n % 2000 - 1000) / 1000);
}

void	set_random(void)
{
	int i;

	i = -1;
	while (++i < 500)
	{
		g_r[i] = (random1() + 1.0) / 2.0;
		g_rp[i].fx = random1();
		g_rp[i].fy = random1();
	}
}

void	find_max(t_vars *vp)
{
	t_pt t;

	g_lvl = 0;
	t.sy = -1;
	while (++t.sy < D >> 4)
	{
		t.sx = -1;
		while (++t.sx < D >> 4)
		{
			if (vp->pl[t.sy][t.sx].wet && vp->pl[t.sy][t.sx].lvl > g_lvl)
				g_lvl = vp->pl[t.sy][t.sx].lvl;
		}
	}
}

int		k_control_mode(int key, t_vars *vp)
{
	if (key == 53)
		exit(1);
	else if (key == 49)
		vp->go = !vp->go;
	else if (key == 83 || key == 84)
		vp->mode = (key == 83 ? 1 : 2);
	else if (key == 85 || key == 86)
		vp->mode = (key == 85 ? 3 : 4);
	else if (key == 87 || key == 88)
	{
		vp->moses = 0;
		vp->mode = (key == 87 ? 5 : 6);
		find_max(vp);
	}
	return (0);
}

int		k_control(int key, void *ptr)
{
	t_vars *vp;

	vp = (t_vars*)ptr;
	if (key == 53 || key == 49 || key == 83 || key == 84 ||
		key == 85 || key == 86 || key == 87 || key == 88)
		return (k_control_mode(key, vp));
	else if (key == 124 || key == 123)
		vp->rot.fz += (key == 124 ? PI / 20 : -PI / 20);
	else if (key == 126 || key == 125)
		vp->rot.fx += (key == 126 ? PI / 20 : -PI / 20);
	else if (key == 18 || key == 19)
	{
		g_color.c1 = (key == 18 ? 0x006324 : 0x6b0011);
		g_color.c2 = (key == 18 ? 0x8ed64f : 0xffdcd6);
	}
	else if (key == 20 || key == 21)
	{
		g_color.c1 = (key == 20 ? 0x8c6d00 : 0x215e34);
		g_color.c2 = (key == 20 ? 0xfff9cc : 0xe1f7f2);
	}
	remake(vp);
	return (1);
}
