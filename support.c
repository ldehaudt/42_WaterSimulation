/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldehaudt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 07:13:32 by ldehaudt          #+#    #+#             */
/*   Updated: 2018/06/23 07:13:36 by ldehaudt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod1.h"

bool			in_bounds(int x, int y)
{
	return (x >= 0 && y >= 0 && x <= D >> 4 && y <= D >> 4);
}

void			reset_visited(t_vars *vp)
{
	t_pt p;

	p.sy = -1;
	while (++p.sy < D >> 4)
	{
		p.sx = -1;
		while (++p.sx < D >> 4)
		{
			vp->pl[p.sy][p.sx].visited = false;
		}
	}
}

unsigned int	t_color(float t, unsigned int c_st, unsigned int c_ed)
{
	unsigned int r;
	unsigned int g;
	unsigned int b;

	r = (unsigned int)((c_st >> 16) * (1 - t) + (c_ed >> 16) * t);
	g = (unsigned int)((c_st >> 8 & 255) * (1 - t) + (c_ed >> 8 & 255) * t);
	b = (unsigned int)((c_st & 255) * (1 - t) + (c_ed & 255) * t);
	return ((unsigned int)((r << 16) + (g << 8) + b));
}

int				p_to_str(t_pt p)
{
	if (p.sx < 0 || p.sx >= W || p.sy < 0 || p.sy >= H)
		return (0);
	return (p.sy * W + p.sx);
}

float			to_screen(t_vars *vp, t_pt *p)
{
	float x;
	float y;
	float z;

	x = p->fx * cos(vp->rot.fz) - p->fy * sin(vp->rot.fz);
	y = p->fy * cos(vp->rot.fz) + p->fx * sin(vp->rot.fz);
	z = p->fz * cos(vp->rot.fx) + y * sin(vp->rot.fx);
	y = (y * cos(vp->rot.fx) - p->fz * sin(vp->rot.fx));
	p->sx = W / 2 + x / (y + 2.8) * W / 2;
	p->sy = (H / 3 - (z - 0.75) / (y + 2.8) * H / 2);
	return (y);
}
