/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 22:14:32 by alacrois          #+#    #+#             */
/*   Updated: 2018/04/27 16:29:04 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*
static void			add_poly_obj(t_obj *o)
{
	while (o->next != NULL)
		o = o->next;
	o->next = (t_obj *)ft_malloc(sizeof(t_obj));
	o->next->type = 5;
	o->next->position = set_rpoint(-2, 0, 0);
	o->next->color = ft_rgb(100, 100, 200, 0);
	o->next->obj = (t_poly_obj *)ft_malloc(sizeof(t_poly_obj));
	o->next->next = NULL;

	((t_poly_obj *)o->next->obj)->vertices = (t_vertex *)ft_malloc(sizeof(t_vertex));
	((t_poly_obj *)o->next->obj)->vertices->next = (t_vertex *)ft_malloc(sizeof(t_vertex));
	((t_poly_obj *)o->next->obj)->vertices->next->next = (t_vertex *)ft_malloc(sizeof(t_vertex));

//	((t_poly_obj *)o->next->obj)->f.p1 = set_rpoint(2, 0, 12);
//	((t_poly_obj *)o->next->obj)->f.p2 = set_rpoint(7, 0, 12);
//	((t_poly_obj *)o->next->obj)->f.p3 = set_rpoint(4, -2, 15);

	((t_poly_obj *)o->next->obj)->vertices->p = set_rpoint(2, 0, 12);
    ((t_poly_obj *)o->next->obj)->vertices->next->p = set_rpoint(7, 0, 12);
    ((t_poly_obj *)o->next->obj)->vertices->next->next->p = set_rpoint(4, -2, 15);
	((t_poly_obj *)o->next->obj)->vertices->next->next->next = NULL;
	((t_poly_obj *)o->next->obj)->next = NULL;
}
*/

static t_env		*init_env(t_rtv1 *r)
{
	t_env			*e;

	e = (t_env *)ft_malloc(sizeof(t_env));
	e->i = (t_img *)ft_malloc(sizeof(t_img));
	e->mlx = mlx_init();
	e->win = mlx_new_window(e->mlx, WIN_SIZE_X, WIN_SIZE_Y, WIN_TITLE);
	e->i->img_p = mlx_new_image(e->mlx, WIN_SIZE_X, WIN_SIZE_Y);
	e->i->img_str = mlx_get_data_addr(e->i->img_p, &(e->i->bpp), \
	&(e->i->line_size), &(e->i->endian));
	e->data = r;
	return (e);
}

static void			init_ray(t_point p, t_rtv1 *r)
{
	r->rays[p.y][p.x].p = r->cam_position;
	r->rays[p.y][p.x].vector.x = p.x - (WIN_SIZE_X / 2);
	r->rays[p.y][p.x].vector.y = p.y - (WIN_SIZE_Y / 2);
	r->rays[p.y][p.x].vector.z = r->screen_distance;
}

static t_env		*init(int ac, char **av)
{
	t_env			*e;
	t_point			p;
	t_rtv1			*r;

	if (ac == 1)
		usage("Error : argument missing.");
	else if (ac > 2)
		usage("Error : too many arguments.");
	r = (t_rtv1 *)ft_malloc(sizeof(t_rtv1));
	r->cam_position.x = 0;
	r->cam_position.y = 0;
	r->cam_position.z = 0;
	r->screen_distance = (WIN_SIZE_X / 2) / tan(FOV / 2);
	p.y = -1;
	while (++p.y < WIN_SIZE_Y)
	{
		p.x = -1;
		while (++p.x < WIN_SIZE_X)
			init_ray(p, r);
	}
	if (parse(r, av[1]) == false)
		usage("Error : invalid argument.");
//	add_poly_obj(r->objects);
	e = init_env(r);
	return (e);
}

static int			exit_window(t_env *e)
{
	if (e != NULL)
		exit(0);
	return (0);
}

int					main(int ac, char **av)
{
	t_env			*e;

	e = init(ac, av);
	draw_image(e);
	mlx_hook(e->win, 17, (1L << 5), exit_window, e);
	mlx_hook(e->win, 2, (1L << 0), key_hook, e);
	mlx_expose_hook(e->win, expose_hook, e);
	mlx_loop(e->mlx);
	return (0);
}
