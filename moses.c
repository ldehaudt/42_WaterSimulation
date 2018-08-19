/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moses.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 06:16:42 by cwu               #+#    #+#             */
/*   Updated: 2018/06/23 06:16:45 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod1.h"

bool	check_stop(t_vars *vp)
{
	bool	stop;
	int		x;

	stop = 1;
	x = -1;
	while (++x <= D >> 4)
		if (vp->pl[x][(D >> 5) + 5].wet == 1
			|| vp->pl[x][(D >> 5) - 5].wet == 1)
			stop = 0;
	if (stop == 1)
	{
		vp->go = 0;
		vp->mode = 1;
		return (1);
	}
	return (0);
}

void	decrease(int y, int x, t_vars *vp)
{
	if (y <= D / 4 && vp->pl[x][y].wet)
	{
		vp->pl[x][y].lvl -= 4;
		if (vp->pl[x][y].lvl > 250 ||
			vp->pl[x][y].lvl <= vp->height[x << 5][y << 5] * 120 + 120)
		{
			vp->pl[x][y].lvl = vp->height[x << 5][y << 5] * 120 + 120;
			vp->pl[x][y].wet = 0;
		}
	}
}

void	moses(t_vars *vp)
{
	int x;
	int i;

	if (check_stop(vp))
		return ;
	i = 0;
	while (i <= vp->moses)
	{
		x = -1;
		while (++x <= D >> 4)
		{
			decrease((D >> 5) + i, x, vp);
			decrease((D >> 5) - i, x, vp);
		}
		i++;
	}
	vp->moses++;
}
