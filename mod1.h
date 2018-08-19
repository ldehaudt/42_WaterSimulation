/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldehaudt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 07:46:42 by ldehaudt          #+#    #+#             */
/*   Updated: 2018/06/23 07:46:44 by ldehaudt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOD1_H
# define MOD1_H
# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>
# include "minilibx_macos/mlx.h"
# include "libft/libft.h"
# include "libft/ft_printf.h"
# define PIX mlx_pixel_put
# define STR mlx_string_put
# define W 1200
# define H 800
# define PI 3.14159265
# define D 2047

typedef struct			s_pt
{
	float				fx;
	float				fy;
	float				fz;
	int					sx;
	int					sy;
}						t_pt;

typedef struct			s_pixel
{
	float				y;
	bool				wet;
}						t_pixel;

typedef struct			s_2d
{
	unsigned char		lvl;
	bool				visited;
	bool				wet;
	bool				wave;
}						t_2d;

typedef struct			s_cpair
{
	unsigned int		c1;
	unsigned int		c2;
}						t_cpair;

typedef struct			s_vars
{
	unsigned char		mode;
	void				*mlx;
	void				*win;
	void				*img;
	char				*str;
	char				*landscape;
	t_2d				**pl;
	t_pixel				*pix;
	t_pt				*map;
	int					npts;
	float				**height;
	float				maxh;
	t_pt				rot;
	float				w;
	bool				go;
	t_pt				f_low;
	int					moses;
}						t_vars;

typedef struct			s_thread
{
	int					mod;
	t_vars				*vp;
	t_pt				p;
	int					n;
}						t_thread;

bool					read_map(t_vars *vp, char *file);
void					draw_walls(t_vars *vp);
int						k_control(int key, void *ptr);
void					init_plane(t_vars *vp);
void					reset_water(t_vars *vp);
void					set_color(void);
void					reset(t_vars *vp);
void					make_landscape(t_vars *vp);
int						refresh(t_vars *vp);
void					remake(t_vars *vp);
void					update_screen(t_vars *vp);
float					to_screen(t_vars *vp, t_pt *p);
void					reset_visited(t_vars *vp);
void					*thread_screen(void *ptr);
void					set_random(void);
float					random1(void);
float					get_h(t_pt p, t_vars *vp);
void					set_height(t_vars *vp);
int						p_to_str(t_pt p);
unsigned int			t_color(float t, unsigned int c_st, unsigned int c_ed);
bool					in_bounds(int x, int y);
void					draw_fishtank(t_vars *vp);
t_pt					drop(t_pt p, t_vars *vp);
void					fill(t_pt p, int n, t_vars *vp);
void					wave(t_vars *vp);
void					rain(t_vars *vp);
void					snow(t_vars *vp);
void					flush(t_vars *vp);
void					moses(t_vars *vp);

float					g_r[500];
t_pt					g_rp[500];
unsigned char			g_lvl;
t_cpair					g_color;
unsigned int			g_lcolor[255];

#endif
