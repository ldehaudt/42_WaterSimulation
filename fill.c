/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uniformfill.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 06:28:56 by cwu               #+#    #+#             */
/*   Updated: 2018/06/23 06:28:59 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod1.h"

t_pt	go_wet(t_pt *p, t_vars *vp)
{
	t_pt t;

	t.sy = -1;
	while (++t.sy <= D >> 4)
	{
		t.sx = -1;
		while (++t.sx <= D >> 4)
			if (vp->pl[t.sy][t.sx].wet)
				if (vp->pl[t.sy][t.sx].lvl < vp->pl[p->sy][p->sx].lvl)
					return (t);
	}
	t.sx = -1;
	return (t);
}

t_pt	go_lower(t_pt *p, t_vars *vp)
{
	t_pt t;

	t.sy = -1;
	while (++t.sy <= D >> 4)
	{
		t.sx = -1;
		while (++t.sx <= D >> 4)
			if (!vp->pl[t.sy][t.sx].wet &&
				((t.sy + 1 < D >> 4 && vp->pl[t.sy + 1][t.sx].wet)
				|| (t.sy - 1 >= 0 && vp->pl[t.sy - 1][t.sx].wet)
				|| (t.sx + 1 < D >> 4 && vp->pl[t.sy][t.sx + 1].wet)
				|| (t.sx - 1 >= 0 && vp->pl[t.sy][t.sx - 1].wet)))
				if (vp->pl[t.sy][t.sx].lvl < vp->pl[p->sy][p->sx].lvl)
				{
					*p = t;
					return (t);
				}
	}
	return (go_wet(p, vp));
}

void	fill(t_pt p, int n, t_vars *vp)
{
	int		i;
	t_pt	t;

	i = -1;
	while (++i < n)
	{
		t = go_lower(&p, vp);
		if (t.sx == -1)
		{
			vp->pl[p.sy][p.sx].lvl++;
			vp->pl[p.sy][p.sx].wet = true;
		}
		else
		{
			vp->pl[t.sy][t.sx].lvl++;
			vp->pl[t.sy][t.sx].wet = true;
		}
	}
}

void	white_water(t_vars *vp, int *ptr)
{
	int i;

	i = 0;
	while (++i <= D >> 4)
	{
		if (i >= *ptr - 4 && i < *ptr)
			vp->pl[0][i].wave = 1;
		else
			vp->pl[0][i].wave = 0;
	}
	if (*ptr >= (D >> 4) + 4)
	{
		vp->mode = 1;
		*ptr = 0;
	}
}

void	wave(t_vars *vp)
{
	static int	x = 0;
	int			y;
	int			i;

	i = -6;
	while (++i <= 0)
	{
		y = -1;
		while (++y <= D >> 4 && 0 <= x + i && x + i <= D >> 4)
			if (vp->pl[y][x + i].wet)
			{
				vp->pl[y][x + i].lvl++;
				if (y + 1 <= D >> 4 && !vp->pl[y + 1][x + i].wet
					&& vp->pl[y + 1][x + i].lvl < vp->pl[0][0].lvl)
					vp->pl[y + 1][x + i].wet = 1;
				if (y - 1 >= 0 && !vp->pl[y - 1][x + i].wet
					&& vp->pl[y - 1][x + i].lvl < vp->pl[0][0].lvl)
					vp->pl[y - 1][x + i].wet = 1;
				if (x + i + 1 <= D >> 4 && !vp->pl[y][x + i + 1].wet
					&& vp->pl[y][x + i + 1].lvl < vp->pl[0][0].lvl)
					vp->pl[y][x + i + 1].wet = 1;
			}
	}
	x++;
	white_water(vp, &x);
}
