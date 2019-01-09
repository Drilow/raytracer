/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 02:57:56 by alacrois          #+#    #+#             */
/*   Updated: 2018/11/29 10:43:07 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <libft.h>
#include <parser/parser.h>
#include <extra/extra_defs.h>
#include <objects/object.h>
#include <fcntl.h>

extern t_global g_global;

static	int		get_object_type(char *s)
{
	if (cmp_chars(s, "light", 0) == true)
		return (1);
	if (cmp_chars(s, "camera", 0) == true)
		return (2);
	if (cmp_chars(s, "objects", 0) == true)
		return (3);
	if (cmp_chars(s, "ambientlight", 0) == true)
		return (4);
	ft_putendl(s);
	return (-1);
}

t_obj			*malloc_object(int type)
{
	t_obj		*o;

	if (!(o = (t_obj *)malloc(sizeof(t_obj))))
		exit(1);
	if (type == 1)
		o->obj = (t_sphere *)malloc(sizeof(t_sphere));
	else if (type == 2)
		o->obj = (t_plane *)malloc(sizeof(t_plane));
	else if (type == 3)
		o->obj = (t_cone *)malloc(sizeof(t_cone));
	else if (type == 4)
		o->obj = (t_cylinder *)malloc(sizeof(t_cylinder));
	o->type = type;
	o->next = NULL;
	return (o);
}

bool			get_started(t_json_value *val)
{
	t_json_object	*obj;
	unsigned long	nb;

	nb = 0;
	obj = (t_json_object *)val->ptr;
	while (nb < obj->nb)
	{
		if (start_parse(obj,
			get_object_type(obj->pair[nb]->key->str), nb) == false)
			return (false);
		nb++;
	}
	return (true);
}

static void		error_view(gchar *text)
{
	static GtkWidget 		*label;
	GtkWidget 				*dialog;

	dialog = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_MOUSE);
	gtk_window_set_default_size(GTK_WINDOW(dialog), 280, 80);
	g_signal_connect(G_OBJECT(dialog), "destroy",
					G_CALLBACK(gtk_widget_destroyed), &dialog);
	gtk_window_set_title (GTK_WINDOW(dialog), "Parser Details");
    gtk_container_set_border_width (GTK_CONTAINER(dialog), 5);
	label = gtk_label_new(text);
	gtk_widget_set_size_request(label, 10, 10);
	gtk_container_add(GTK_CONTAINER(dialog), label);
	gtk_widget_show_all(dialog);
}

bool			parse(char *file)
{
	int				fd;
	char			*str;
	t_json_value	*val;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (false);
	g_global.r->objects = NULL;
	g_global.r->lights = NULL;
	g_global.r->ambient_light = ft_rgb(0, 0, 0, 0);
	str = ft_readfile(fd, file);
	if ((val = json_init(str)) == NULL)
	{
		ft_putendl("Parse failed.");
		ft_free(str);
		return (false);
	}
	ft_free(str);
	error_view("jambon");
	if (get_started(val) == false)
		return (false);
	close(fd);
	return (true);
}
