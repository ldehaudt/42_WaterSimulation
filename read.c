/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldehaudt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 04:25:13 by ldehaudt          #+#    #+#             */
/*   Updated: 2018/06/23 04:25:35 by ldehaudt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod1.h"

int		number(char **sp)
{
	int		i;
	int		nbr;
	char	*str;

	str = *sp;
	i = 0;
	if (str[0] == '-')
		i++;
	while (str[i] && str[i] != ' ')
	{
		if (!isdigit(str[i]))
			return (INT_MIN + 17);
		i++;
	}
	i++;
	nbr = ft_atoi(str);
	*sp = cw_strchop(str, i);
	return (nbr);
}

bool	read_points(t_vars *vp, int fd)
{
	char	*line;
	int		lc;

	lc = 0;
	while (ft_gnl(fd, &line))
	{
		if (cw_countw(line, ' ') != 3 || lc >= 20)
			return (false);
		vp->map[lc].fx = (float)number(&line) / 50;
		if (vp->map[lc].fx < -1 || vp->map[lc].fx > 1)
			return (false);
		vp->map[lc].fy = (float)number(&line) / 50;
		if (vp->map[lc].fy < -1 || vp->map[lc].fy > 1)
			return (false);
		vp->map[lc].fz = (float)number(&line) / 50 - 1;
		if (vp->map[lc].fz < -1 || vp->map[lc].fz > 1)
			return (false);
		free(line);
		lc++;
	}
	vp->npts = lc;
	return (true);
}

bool	read_map(t_vars *vp, char *file)
{
	int		fd;
	int		lc;

	fd = open(file, O_RDONLY);
	if (fd == -1 || read(fd, NULL, 0) == -1)
		return (false);
	vp->map = (t_pt*)malloc(sizeof(t_pt) * 21);
	if (!read_points(vp, fd))
	{
		close(fd);
		ft_printf("{O}Valid file must contain 0-20 point x y z, where:\n");
		ft_printf("{O}-50 <= x <= 50; -50 <= y <= 50; 0 <= z <= 100\n");
		return (false);
	}
	close(fd);
	vp->maxh = 0;
	lc = 0;
	while (lc < vp->npts)
	{
		if (vp->map[lc].fz + 1 > vp->maxh * 2)
			vp->maxh = (vp->map[lc].fz + 1) / 2;
		lc++;
	}
	return (true);
}
