/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   landscape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldehaudt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 04:33:33 by ldehaudt          #+#    #+#             */
/*   Updated: 2018/06/23 04:33:34 by ldehaudt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod1.h"

float	d(t_pt p1, t_pt p2)
{
	t_pt delta;

	delta.fx = fabsf(p2.fx - p1.fx);
	delta.fy = fabsf(p2.fy - p1.fy);
	return (sqrt(pow(delta.fx, 2) + pow(delta.fy, 2)));
}

float	height(t_pt p, t_vars *vp)
{
	float	sum;
	float	dist;
	float	invd;
	int		i;

	invd = (p.fx + 1 < 1 - p.fx ? p.fx + 1 : 1 - p.fx);
	if (p.fy + 1 < invd)
		invd = p.fy + 1;
	if (1 - p.fy < invd)
		invd = 1 - p.fy;
	if (invd < 0.001)
		return (-1);
	dist = 1.0 / invd;
	sum = -dist;
	i = -1;
	while (++i < vp->npts)
	{
		invd = d(p, vp->map[i]) * d(p, vp->map[i]);
		if (invd < 0.0001)
			return (vp->map[i].fz);
		invd = 1.0 / invd;
		dist += invd;
		sum += invd * vp->map[i].fz;
	}
	return (sum / dist);
}

void	*height_multithread(void *ptr)
{
	t_thread	*t;
	t_pt		p;

	t = (t_thread*)ptr;
	p.sy = 0;
	while (p.sy < 2 * D)
	{
		p.sx = t->mod;
		while (p.sx < 2 * D)
		{
			p.fx = (float)p.sx / D - 1.0;
			p.fy = (float)p.sy / D - 1.0;
			t->vp->height[p.sy][p.sx] = height(p, t->vp);
			p.sx += 4;
		}
		p.sy++;
	}
	return (NULL);
}

void	set_height(t_vars *vp)
{
	t_thread	t[4];
	pthread_t	id[4];
	int			i;

	i = 0;
	vp->height = (float**)malloc(sizeof(float*) * (2 * D + 1));
	while (i < 2 * D)
	{
		vp->height[i] = (float*)malloc(sizeof(float) * (2 * D + 1));
		i++;
	}
	i = -1;
	while (++i < 4)
	{
		t[i].mod = i;
		t[i].vp = vp;
		pthread_create(&id[i], NULL, height_multithread, (void *)(&t[i]));
	}
	pthread_join(id[0], NULL);
	pthread_join(id[1], NULL);
	pthread_join(id[2], NULL);
	pthread_join(id[3], NULL);
}

void	make_landscape(t_vars *vp)
{
	t_pt	p;
	int		c;
	float	y;

	set_color();
	reset(vp);
	p.fy = -1;
	while (p.fy < 1)
	{
		p.fx = -1;
		while (p.fx < 1)
		{
			p.fz = get_h(p, vp);
			y = to_screen(vp, &p);
			c = p_to_str(p);
			if (y < vp->pix[c].y)
			{
				((unsigned int*)vp->landscape)[c] = (vp->maxh ?
				g_lcolor[(int)((p.fz + 1) * 127 / vp->maxh)] : g_lcolor[0]);
				vp->pix[c].y = y;
			}
			p.fx += 2.0 / D;
		}
		p.fy += 2.0 / D;
	}
}
