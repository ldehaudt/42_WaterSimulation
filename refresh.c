/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldehaudt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 06:58:10 by ldehaudt          #+#    #+#             */
/*   Updated: 2018/06/23 06:58:11 by ldehaudt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod1.h"

void		reset_water(t_vars *vp)
{
	int		i;
	t_pt	p;

	(void)vp;
	i = -1;
	while (++i < W * H)
		vp->pix[i].wet = false;
	p.fy = -1;
}

void		run_mode(t_vars *vp, t_pt p)
{
	if (vp->mode == 1)
		fill(p, 3000, vp);
	else if (vp->mode == 2)
		wave(vp);
	else if (vp->mode == 3)
		rain(vp);
	else if (vp->mode == 4)
		snow(vp);
	else if (vp->mode == 5)
		flush(vp);
	else if (vp->mode == 6)
		moses(vp);
}

void		update_screen(t_vars *vp)
{
	t_thread	t[4];
	pthread_t	id[4];
	int			i;

	i = -1;
	while (++i < 4)
	{
		t[i].mod = i;
		t[i].vp = vp;
		pthread_create(&id[i], NULL, thread_screen, (void *)(&t[i]));
	}
	pthread_join(id[0], NULL);
	pthread_join(id[1], NULL);
	pthread_join(id[2], NULL);
	pthread_join(id[3], NULL);
	draw_walls(vp);
}

int			refresh(t_vars *vp)
{
	int		i;
	t_pt	p;

	p.sx = 0;
	p.sy = 0;
	if (vp->go)
	{
		p.fx = 0;
		p.fy = 0;
		i = -1;
		while (++i < W * H)
			((unsigned int*)vp->str)[i] = ((unsigned int*)vp->landscape)[i];
		reset_water(vp);
		run_mode(vp, p);
		update_screen(vp);
		mlx_put_image_to_window(vp->mlx, vp->win, vp->img, 0, 0);
	}
	return (0);
}

void		remake(t_vars *vp)
{
	make_landscape(vp);
	if (vp->go == false)
	{
		vp->go = true;
		refresh(vp);
		vp->go = false;
	}
}
