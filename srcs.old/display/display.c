#include <libft.h>
#include <thread/thread.h>
#include <rt.h>
#include <sdl_stuff/sdl_mgr.h>
#include <raytracing/collision.h>
#include <global.h>
#include <extra/extra_defs.h>
#include <geometry/geometry.h>

extern t_global	g_global;

/*
//static void			*draw_image_core(void *arg)
void				draw_image(t_sdl_wrapper *e)
{
//	t_thread		th;
//	t_sdl_wrapper	*e;
	t_point			p;
	t_rt			*r;
	t_collision		tmp;

//	th = *((t_thread *)arg);
//	e = th.e;
	r = &g_global.r;
//	p.x = th.th_index;
	p.x = 0;
	while (p.x < WIN_W)
	{
		p.y = -1;
//		if (th.th_index == 0)
//		{
			ft_putnbr(p.x);
			ft_putstr(" / ");
			ft_putnbr(WIN_W);
			ft_putstr("\n");
//		}
		while (++p.y < WIN_H)
		{
			tmp = ray_tracing(r, r->rays[p.y][p.x]);
			if (tmp.o != NULL)
				draw_px(e->surf, p.x, p.y, \
						get_ray_color(r, tmp));
//get_ray_color(r, tmp.o, tmp.p));
			else
				draw_px(e->surf, p.x, p.y, ft_rgb(0, 0, 0, 0));
		}
//		p.x = p.x + THREADS_NB;
		p.x++;
	}
	g_global.drawn = 0;
}
*/


static void		*draw_image_core(void *arg)
{
	t_thread	th;
	t_sdl_wrapper		*e;
	t_point		p;
	t_rt		*r;
	t_collision	tmp;
//	t_rgb		tmpclr;

	th = *((t_thread *)arg);
	e = th.e;
	r = &g_global.r;
	p.x = th.th_index;
	while (p.x < WIN_W)
	{
		p.y = -1;

		if (th.th_index == 0)
		{
			ft_putnbr(p.x);
			ft_putstr(" / ");
			ft_putnbr(WIN_W);
			ft_putstr("\n");
		}

		while (++p.y < WIN_H)
		{
			tmp = ray_tracing(r, r->rays[p.y][p.x], false);
			if (tmp.o != NULL)
			{
//				if ((p.x == 361 || p.x == 360) && p.y == 209)
//				if (p.x == 360 && p.y == 209)
//					tmpclr = get_ray_color(r, tmp, true);
//				else
//					tmpclr = get_ray_color(r, tmp, false);
//				if (tmp.o->type == 2 && tmpclr.g < 50 && p.y > 200)
//				{
//					printf("incorrect pixel (%d, %d) : ", p.x, p.y);
//					printf("rgb(%d, %d, %d)\n", tmpclr.r, tmpclr.g, tmpclr.b);
//				}
//				if (p.x == 361 && p.y == 209)
//					printf("correct(361, 209) : rgb(%d, %d, %d)\n", tmpclr.r, tmpclr.g, tmpclr.b);
				draw_px(e->surf, p.x, p.y, \
						get_ray_color(r, tmp, false));
//				get_ray_color(r, tmp.o, tmp.p));
			}
			else
			{
//				if (p.y > 120)
//					printf("Black pixel : x=%d & y=%d\n", p.x, p.y);
				draw_px(e->surf, p.x, p.y, ft_rgb(0, 0, 0, 0));
			}
		}
		p.x = p.x + THREADS_NB;
	}
	pthread_exit(NULL);
}

void			draw_image(t_sdl_wrapper *e)
{
	pthread_t	threads[THREADS_NB];
	t_thread	th_arg[THREADS_NB];
	int			i;

	i = 0;
	while (i < THREADS_NB)
	{
		th_arg[i].e = e;
		th_arg[i].th_index = i;
		if (pthread_create(&(threads[i]), NULL, draw_image_core, \
			&th_arg[i]) != 0)
			ft_exit("Thread could not be created.", 1);
		i++;
	}
	while (i > 0)
	{
		i--;
		if (pthread_join(threads[i], NULL) != 0)
			ft_exit("Thread could not be joined.", 1);
	}
	g_global.drawn = 0;
}
