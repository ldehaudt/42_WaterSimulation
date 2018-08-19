/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rain.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldehaudt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 05:33:39 by ldehaudt          #+#    #+#             */
/*   Updated: 2018/06/23 05:33:41 by ldehaudt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod1.h"

static float g_t = 0;
bool g_first = true;

bool	flow(t_pt *p, t_vars *vp)
{
	unsigned char	low;
	int				nx;
	int				ny;
	t_pt			low_pt;

	low_pt.sx = p->sx;
	low_pt.sy = p->sy;
	ny = p->sy - 5;
	low = vp->pl[p->sy][p->sx].lvl;
	while (++ny <= p->sy + 4 && (nx = p->sx - 5) != -42)
	{
		while (++nx <= p->sx + 4)
			if (in_bounds(nx, ny) && (nx != p->sx || ny != p->sy)
				&& vp->pl[ny][nx].lvl <= low && vp->pl[ny][nx].visited == false)
			{
				vp->pl[ny][nx].visited = true;
				low = vp->pl[ny][nx].lvl;
				low_pt.sx = nx;
				low_pt.sy = ny;
			}
	}
	nx = (low_pt.sx == p->sx && low_pt.sy == p->sy) ? 0 : 1;
	p->sx = low_pt.sx;
	p->sy = low_pt.sy;
	return (nx);
}

void	rain_fill(t_pt p, int n, t_vars *vp)
{
	int i;

	i = -1;
	while (++i < n)
	{
		reset_visited(vp);
		while (flow(&p, vp))
			vp->pl[p.sy][p.sx].visited = true;
		vp->pl[p.sy][p.sx].lvl++;
		vp->pl[p.sy][p.sx].wet = true;
	}
}

void	start_rain_fill(t_vars *vp)
{
	int		i;
	t_pt	t;

	i = -1;
	while (++i < 50)
	{
		t.sy = (((random1()) + 1) / 2.0) * (D >> 4);
		t.sx = (((random1()) + 1) / 2.0) * (D >> 4);
		rain_fill(t, 5, vp);
	}
}

void	draw_rain(t_vars *vp, int i, int n, unsigned int loc)
{
	g_rp[i].fz = 2 - ((float)(240 - g_lvl) / 120 + 1) *
	((g_t + g_r[i] - (int)(g_t + g_r[i])));
	to_screen(vp, &g_rp[i]);
	n = p_to_str(g_rp[i]);
	loc = ((unsigned int*)vp->str)[n + W];
	((unsigned int*)vp->str)[n - 3 * W] = t_color(0.9, 0x8ecce2, loc);
	((unsigned int*)vp->str)[n - 3 * W + 1] =
	((unsigned int*)vp->str)[n - 3 * W];
	((unsigned int*)vp->str)[n - 2 * W] = t_color(0.8, 0x8ecce2, loc);
	((unsigned int*)vp->str)[n - 2 * W + 1] =
	((unsigned int*)vp->str)[n - 2 * W];
	((unsigned int*)vp->str)[n - W] = t_color(0.7, 0x8ecce2, loc);
	((unsigned int*)vp->str)[n - W + 1] = ((unsigned int*)vp->str)[n - W];
	((unsigned int*)vp->str)[n] = t_color(0.6, 0x8ecce2, loc);
	((unsigned int*)vp->str)[n + 1] = ((unsigned int*)vp->str)[n];
	((unsigned int*)vp->str)[n + W] = t_color(0.4, 0x8ecce2, loc);
	((unsigned int*)vp->str)[n + W + 1] = ((unsigned int*)vp->str)[n + W];
	((unsigned int*)vp->str)[n + W * 2] = t_color(0.3, 0x8ecce2, loc);
	((unsigned int*)vp->str)[n + W * 2 + 1] =
	((unsigned int*)vp->str)[n + W * 2];
}

void	rain(t_vars *vp)
{
	int				i;
	int				n;
	unsigned int	loc;

	n = 0;
	loc = 0;
	i = -1;
	while (++i < 100)
	{
		draw_rain(vp, i, n, loc);
	}
	start_rain_fill(vp);
	g_t += 0.03;
}
