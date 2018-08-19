/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldehaudt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 06:51:56 by ldehaudt          #+#    #+#             */
/*   Updated: 2018/06/23 06:51:58 by ldehaudt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod1.h"

void			reset(t_vars *vp)
{
	int i;

	i = 0;
	while (i < W * H)
	{
		((unsigned int*)vp->landscape)[i] = 0;
		vp->pix[i].y = (float)INT_MAX;
		i++;
	}
}

void			add_wall(t_vars *vp, t_pt p, bool hor)
{
	int				i;
	float			y;
	float			h;
	unsigned int	col;

	while ((p.fx < 1 && hor) || (p.fy < 1 && !hor))
	{
		h = -1;
		while (h <= vp->pl[(int)(p.fy * D + D) >> 5][(int)(p.fx * D + D)
		>> 5].lvl / 120.0 - 1)
		{
			p.fz = h;
			y = to_screen(vp, &p);
			i = p_to_str(p);
			if (y < vp->pix[i].y && !vp->pix[i].wet && (vp->pix[i].wet = true))
			{
				col = t_color(0.5, ((unsigned int*)vp->str)[i],
				(hor ? 0x2460a0 : 0x16497c));
				((unsigned int*)vp->str)[i] = (vp->mode == 4 ? 0xdce4ef : col);
			}
			h += 5.0 / D;
		}
		p.fx += (hor ? 5.0 / D : 0);
		p.fy += (!hor ? 5.0 / D : 0);
	}
}

void			screen_val(t_vars *vp, t_pt p, int i, t_pt d)
{
	if ((vp->pl[(int)(p.fy * D + D) >> 5][(int)(p.fx * D + D) >> 5].wet
	|| vp->pl[(int)(p.fy * D + D) >> 5][((int)(p.fx * D + D) >> 5) + 1].wet)
		&& d.fx < vp->pix[i].y && !vp->pix[i].wet && 0 < i && i < H * W)
	{
		vp->pix[i].wet = true;
		if (vp->mode == 4)
			((unsigned int*)vp->str)[i] = 0xffffff;
		else if (vp->mode == 2 && vp->pl[0][(int)(p.fx * D + D)
		>> 5].wave)
			((unsigned int*)vp->str)[i] = t_color(0.7,
			((unsigned int*)vp->str)[i], 0xabe4f2);
		else if ((d.sx > 3 && vp->mode != 2) ||
		(d.sx > 4 && vp->mode == 2))
			((unsigned int*)vp->str)[i] = t_color(0.5,
			((unsigned int*)vp->str)[i], 0x48b0d6);
		else if (d.sx >= 0)
			((unsigned int*)vp->str)[i] =
				t_color(0.6, ((unsigned int*)vp->str)[i], 0xabe4f2);
	}
}

/*
** t_pt d holds differance (water) var in sx and depth (screen) in fx
*/

void			*thread_screen(void *ptr)
{
	t_thread	*t;
	t_pt		p;
	int			i;
	t_pt		d;

	t = (t_thread*)ptr;
	p.fy = (t->mod >= 2) ? 0 : -1;
	while (p.fy < ((t->mod >= 2) ? 1.0f : 0.0f))
	{
		p.fx = (t->mod == 2 || t->mod == 0) ? -1 : 0;
		while (p.fx < ((t->mod == 2 || t->mod == 0) ? 0.0f : 1.0f))
		{
			p.fz = ((t->vp->pl[(int)(p.fy * D + D) >> 5]
		[(int)(p.fx * D + D) >> 5].lvl) / 120.0) - 1;
			d.fx = to_screen(t->vp, &p);
			i = p_to_str(p);
			d.sx = t->vp->pl[(int)(p.fy * D + D) >> 5][(int)(p.fx * D + D) >>
5].lvl - (t->vp->height[(int)(p.fy * D + D)][(int)(p.fx * D + D)] * 120 + 120);
			screen_val(t->vp, p, i, d);
			p.fx += 4.0 / D;
		}
		p.fy += 4.0 / D;
	}
	return (NULL);
}

void			draw_walls(t_vars *vp)
{
	t_pt p;

	p.fy = -1;
	p.fx = -1;
	add_wall(vp, p, false);
	p.fy = -1;
	p.fx = 1;
	add_wall(vp, p, false);
	p.fy = -1;
	p.fx = -1;
	add_wall(vp, p, true);
	p.fy = 1;
	p.fx = -1;
	add_wall(vp, p, true);
}
