/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snow.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldehaudt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 04:23:24 by ldehaudt          #+#    #+#             */
/*   Updated: 2018/06/23 04:23:25 by ldehaudt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod1.h"

static float g_t = 0;

t_pt	drop(t_pt p, t_vars *vp)
{
	t_pt			t;
	unsigned char	l;

	l = vp->pl[p.sy][p.sx].lvl;
	t = p;
	if (p.sx > 0 && vp->pl[p.sy][p.sx - 1].lvl < l)
		t.sx--;
	else if (p.sx + 1 < D >> 4 && vp->pl[p.sy][p.sx + 1].lvl < l)
		t.sx++;
	else if (p.sy > 0 && vp->pl[p.sy - 1][p.sx].lvl < l)
		t.sy--;
	else if (p.sy + 1 < D >> 4 && vp->pl[p.sy + 1][p.sx].lvl < l)
		t.sy++;
	return (t);
}

void	snow_fill(t_pt p, int n, t_vars *vp)
{
	int		i;
	t_pt	t;

	i = -1;
	while (++i < n)
	{
		while ((t = drop(p, vp)).sx != p.sx || t.sy != p.sy)
			p = t;
		vp->pl[p.sy][p.sx].lvl++;
		vp->pl[p.sy][p.sx].wet = true;
	}
}

void	start_snow_fill(t_vars *vp)
{
	int		i;
	t_pt	t;

	i = -1;
	while (++i < 100)
	{
		t.sy = (((random1()) + 1) / 2.0) * (D >> 4);
		t.sx = (((random1()) + 1) / 2.0) * (D >> 4);
		snow_fill(t, 1, vp);
	}
}

void	snow(t_vars *vp)
{
	int				i;
	int				n;
	unsigned int	loc;
	t_pt			t;

	i = -1;
	while (++i < 500)
	{
		g_rp[i].fz = 2 - ((float)(240 - g_lvl) / 120 + 1) *
		((g_t + g_r[i] - (int)(g_t + g_r[i])));
		to_screen(vp, &g_rp[i]);
		n = p_to_str(g_rp[i]);
		loc = ((unsigned int*)vp->str)[n + W];
		((unsigned int*)vp->str)[n - W] = t_color(0.5, 0xffffff, loc);
		((unsigned int*)vp->str)[n - 1] = t_color(0.5, 0xffffff, loc);
		((unsigned int*)vp->str)[n] = 0xffffff;
		((unsigned int*)vp->str)[n + 1] = t_color(0.5, 0xffffff, loc);
		((unsigned int*)vp->str)[n + W] = t_color(0.5, 0xffffff, loc);
		t.sy = (g_rp[i].fy + 1) / 2 * (D >> 4);
		t.sx = (g_rp[i].fx + 1) / 2 * (D >> 4);
	}
	start_snow_fill(vp);
	g_t += 0.005;
}

void	flush(t_vars *vp)
{
	t_pt t;

	if (g_lvl == 0)
	{
		vp->mode = 1;
		vp->go = 0;
		return ;
	}
	t.sy = -1;
	while (++t.sy <= D >> 4)
	{
		t.sx = -1;
		while (++t.sx <= D >> 4)
		{
			if (vp->pl[t.sy][t.sx].wet && vp->pl[t.sy][t.sx].lvl > g_lvl)
			{
				vp->pl[t.sy][t.sx].lvl = g_lvl;
				if (vp->height[t.sy << 5][t.sx << 5] >
				(float)(g_lvl - 120) / 120.0)
					vp->pl[t.sy][t.sx].wet = 0;
			}
		}
	}
	g_lvl--;
}
