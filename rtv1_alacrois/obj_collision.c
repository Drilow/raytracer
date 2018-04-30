/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_collision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 15:30:52 by alacrois          #+#    #+#             */
/*   Updated: 2018/04/30 19:00:16 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static t_rpoint	add_rpoints(t_rpoint a, t_rpoint b)
{
	return (set_rpoint(a.x + b.x, a.y + b.y, a.z + b.z));
}

static t_bool	face_collision(t_ray ray, t_rpoint pos, t_vertex *face, t_collision *col)
{
	t_rpoint	tmp;
	double		a;
	t_vertex	*tmpv;

	if (plane_collision(ray, &(face->pl), &tmp) == false)
		return (false);
	tmpv = face;
	a = 0;
	while (tmpv->next != NULL)
	{
		a = a + vangle(get_vector(tmp, add_rpoints(pos, tmpv->p)), get_vector(tmp, add_rpoints(pos, tmpv->next->p)));
		tmpv = tmpv->next;
	}
	a = a + vangle(get_vector(tmp, add_rpoints(pos, tmpv->p)), get_vector(tmp, add_rpoints(pos, face->p)));
	if (a < (2 * PI) * 0.999999 || a > (2 * PI) * 1.000001)
		return (false);
	col->normal = face->pl.vector;
	col->p = tmp;
	return (true);
}

// 'poly_obj_collision' fonctionnement par defaut ====>
t_bool			poly_obj_collision(t_ray ray, t_poly_obj *po, t_collision *col)
{
	t_collision	fcol;
	t_collision	tmp;
	double		d;
	t_poly_obj	*potmp;

	d = -1;
	potmp = po;
	// NEW ====>
	// skip le calcul si la distance entre la droite forme par le rayon et l'objet est superieure a la distance max possible entre la position de l'objet et un de ses points (===> pas de collision possible)
	// ca fait gagner un peu de temps de calcul... (a enlever pour voir la difference)
	if (point_to_line_distance(col->o->position, ray.p, ray.vector) > po->max_d)
		return (false);
	// <=== NEW
	while (potmp != NULL)
	{
		if (face_collision(ray, col->o->position, potmp->vertices, &tmp) == true && (d == -1 || deltasq(ray.p, tmp.p) < d))
		{
			fcol = tmp;
			d = deltasq(ray.p, tmp.p);
		}
		potmp = potmp->next;
	}

	if (d == -1)
		return (false);
	*col = fcol;
	return (true);
}
// <==== 'poly_obj_collision' fonctionnement par defaut

// 'poly_obj_collision' en multithreading (mettre celle dessus en commentaire
// et enlever les commentaires en dessous pour activer)
// NOTE : pour l;instant le resultat afficher est mauvais (resultat absurde)
 /*
static t_poly_obj	*next_po(t_poly_obj *o, int index)
{
	while (o != NULL && index > 0)
	{
		index--;
		o = o->next;
	}
	return (o);
}

static void		*poly_obj_collision_core(void *arg)
{
	t_ray		ray;
	t_poly_obj	*po;
	t_collision	*col;
    t_collision fcol;
    t_collision tmp;
    double      d;
    t_poly_obj  *potmp;

	ray = ((t_thread *)arg)->ray;
	po = ((t_thread *)arg)->po;
	col = ((t_thread *)arg)->col;
	d = -1;
	potmp = next_po(po, ((t_thread *)arg)->th_index);
	fcol.c = false;
    while (potmp != NULL)
    {
        if (face_collision(ray, col->o->position, potmp->vertices, &tmp) == true && \
			(d == -1 || deltasq(ray.p, tmp.p) < d))
        {
            fcol = tmp;
			fcol.c = true;
            d = deltasq(ray.p, tmp.p);
        }
		potmp = next_po(potmp, OBJ_THREADS_NB);
    }
    if (d == -1)
		return (NULL);
    *col = fcol;
	pthread_exit(NULL);
}

t_bool			poly_obj_collision(t_ray ray, t_poly_obj *po, t_collision *col)
{
	pthread_t	threads[OBJ_THREADS_NB];
	t_thread	th_arg[OBJ_THREADS_NB];
	int			i;
	t_collision	tmp;

	i = 0;
	if (point_to_line_distance(col->o->position, ray.p, ray.vector) > po->max_d)
		return (false);
	while (i < OBJ_THREADS_NB)
	{
		th_arg[i].th_index = i;
		th_arg[i].ray = ray;
		th_arg[i].po = po;
		th_arg[i].col = (t_collision *)ft_malloc(sizeof(t_collision));
		th_arg[i].col->o = col->o;
		if (pthread_create(&(threads[i]), NULL, poly_obj_collision_core, \
			&th_arg[i]) != 0)
			ft_exit("Thread could not be created.");
		i++;
	}
	while (i > 0)
	{
		i--;
		if (pthread_join(threads[i], NULL) != 0)
			ft_exit("Thread could not be joined.");
	}
	tmp.c = false;
	while (i < OBJ_THREADS_NB)
	{
		if (tmp.c == false && th_arg[i].col->c == true)
			tmp = *th_arg[i].col;
		else if (th_arg[i].col->c == true && deltasq(ray.p, th_arg[i].col->p) < deltasq(ray.p, tmp.p))
			tmp = *th_arg[i].col;
		free(th_arg[i].col);
		i++;
	}
	if (tmp.c == true)
		*col = tmp;
	return (tmp.c);
}
*/
