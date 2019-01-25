/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dagnear <Dagnear@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 15:47:04 by adleau            #+#    #+#             */
/*   Updated: 2019/01/25 13:44:27 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <parser/parser.h>
#include <fcntl.h>
#include <libft.h>
#include <display/display.h>

extern t_global		g_global;

void				handle_edit_validation(t_obj *o)
{
	int		r;

	r = gtk_dialog_run(GTK_DIALOG(ADD_VIEW.win));
	if (r == GTK_RESPONSE_ACCEPT)
	{
		validate_edit(o);
		if (ADD_VIEW.win && GTK_IS_WIDGET(ADD_VIEW.win))
		{
			gtk_widget_destroy(GTK_WIDGET(ADD_VIEW.win));
			ADD_VIEW.win = NULL;
		}
	}
	else if (r == GTK_RESPONSE_REJECT)
	{
		redraw(false);
		if (!(ft_strcmp(gtk_window_get_title(GTK_WINDOW(ADD_VIEW.win)),
			"Add Object")))
		{
			g_global.r.objects = o->next;
			free(o->obj);
			o->obj = NULL;
			free(o);
			o = NULL;
		}
		gtk_widget_destroy(GTK_WIDGET(ADD_VIEW.win));
	}
}

void				destroy_ui_for_poly(void)
{
	gtk_widget_destroy(ADD_VIEW.scale_img);
	gtk_widget_destroy(ADD_VIEW.scale_spin);
	gtk_widget_destroy(ADD_VIEW.file_check);
	gtk_widget_destroy(ADD_VIEW.same);
	gtk_widget_destroy(ADD_VIEW.from_template);
	if (ADD_VIEW.cube)
	{
		gtk_widget_destroy(ADD_VIEW.cube);
		gtk_widget_destroy(ADD_VIEW.tetra);
		gtk_widget_destroy(ADD_VIEW.dode);
		gtk_widget_destroy(ADD_VIEW.pyramid);
	}
}

void				destroy_interface_for_type(int type)
{
	if (type == 1 || type == 4)
	{
		gtk_widget_destroy(ADD_VIEW.scale_img);
		gtk_widget_destroy(ADD_VIEW.scale_spin);
	}
	if (type == 2 || type == 3 || type == 4)
	{
		gtk_widget_destroy(ADD_VIEW.vector_x);
		gtk_widget_destroy(ADD_VIEW.vector_y);
		gtk_widget_destroy(ADD_VIEW.vector_z);
		gtk_widget_destroy(ADD_VIEW.vector_img);
	}
	if (type == 3 || type == 4)
	{
		if (type == 3)
		{
			gtk_widget_destroy(ADD_VIEW.angle_img);
			gtk_widget_destroy(ADD_VIEW.angle_spin);
		}
		gtk_widget_destroy(ADD_VIEW.infinite);
		gtk_widget_destroy(ADD_VIEW.inf_img);
	}
	if (type == 6 || type / 10 == 6)
		destroy_ui_for_poly();
}

void				create_inner_obj_for_type(t_obj *tmp, int type)
{
	if (type == 1)
	{
		tmp->obj = (t_sphere*)malloc(sizeof(t_sphere));
		tmp->type = 1;
	}
	else if (type == 2)
	{
		tmp->obj = (t_plane*)malloc(sizeof(t_plane));
		tmp->type = 2;
	}
	else if (type == 3)
	{
		tmp->obj = (t_cone*)malloc(sizeof(t_cone));
		tmp->type = 3;
	}
	else if (type == 4)
	{
		tmp->obj = (t_cylinder*)malloc(sizeof(t_cylinder));
		tmp->type = 4;
	}
	else if (type == 6 || type / 10 == 6)
	{
		tmp->obj = (t_poly_obj*)malloc(sizeof(t_poly_obj));
		tmp->type = 6;
	}
}

void				create_object(t_obj *o, int type)
{
	t_obj			*tmp;

	if (!(tmp = (t_obj*)malloc(sizeof(t_obj))))
		exit_properly(1);
	create_inner_obj_for_type(tmp, type);
	set_default_values(tmp);
	free(o->obj);
	o->type = tmp->type;
	o->obj = tmp->obj;
}
