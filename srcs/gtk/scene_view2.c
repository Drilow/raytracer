/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_view2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 12:54:02 by adleau            #+#    #+#             */
/*   Updated: 2019/02/06 14:47:38 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>

extern t_global			g_global;

static char				*get_obj_type(int type)
{
	if (type == 1)
		return ("Sphère");
	else if (type == 2)
		return ("Plane");
	else if (type == 3)
		return ("Cone");
	else if (type == 4)
		return ("Cylinder");
	else if (type == 6)
		return ("Poly");
	else if (type == 66)
		return ("Cube");
	else if (type == 67)
		return ("Tetra");
	else if (type == 68)
		return ("Pyramid");
	else if (type == 69)
		return ("Dodeca");
	return (NULL);
}

static void				read_obj(t_obj *obj)
{
	GtkTreeIter			iter1;

	gtk_tree_store_append(g_global.r.gtk_mgr.ui.scene_view.store, &iter1, NULL);
	gtk_tree_store_set(g_global.r.gtk_mgr.ui.scene_view.store, &iter1,
					TYPE_COLUMN, get_obj_type(obj->type),
					POS_X_COLUMN, obj->position.x,
					POS_Y_COLUMN, obj->position.y,
					POS_Z_COLUMN, obj->position.z,
					CHECKED_COLUMN, obj->enabled,
					CHECKED_ACTIVE, TRUE,
					OBJ_REF, (gpointer)obj,
					-1);
}

static void				read_light(t_light *light)
{
	GtkTreeIter			iter1;

	gtk_tree_store_append(g_global.r.gtk_mgr.ui.scene_view.store, &iter1, NULL);
	gtk_tree_store_set(g_global.r.gtk_mgr.ui.scene_view.store, &iter1,
					TYPE_COLUMN, "Light",
					POS_X_COLUMN, light->source.x,
					POS_Y_COLUMN, light->source.y,
					POS_Z_COLUMN, light->source.z,
					CHECKED_COLUMN, light->enabled,
					CHECKED_ACTIVE, TRUE,
					OBJ_REF, (gpointer)light,
					-1);
}

static void				populate_tree_model(GtkTreeStore *store)
{
	GtkTreeIter			iter1;
	t_obj				*tmp_objs;
	t_light				*tmp_lights;

	tmp_objs = g_global.r.objects;
	tmp_lights = g_global.r.lights;
	while (tmp_objs != NULL)
	{
		read_obj(tmp_objs);
		tmp_objs = tmp_objs->next;
	}
	while (tmp_lights != NULL)
	{
		read_light(tmp_lights);
		tmp_lights = tmp_lights->next;
	}
	gtk_tree_store_append(store, &iter1, NULL);
	gtk_tree_store_set(store, &iter1, TYPE_COLUMN, "Camera",
					POS_X_COLUMN, g_global.r.cam_position.x,
					POS_Y_COLUMN, g_global.r.cam_position.y,
					POS_Z_COLUMN, g_global.r.cam_position.z,
					CHECKED_COLUMN, TRUE,
					CHECKED_ACTIVE, FALSE,
					OBJ_REF, (gpointer)&g_global.r.cam_position, -1);
}

void					init_scene_view(void)
{
	GtkCellRenderer		*render;

	g_global.r.gtk_mgr.ui.scene_view.win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(
	g_global.r.gtk_mgr.ui.scene_view.win), "Scene");
	gtk_window_set_transient_for(
	GTK_WINDOW(g_global.r.gtk_mgr.ui.scene_view.win),
	GTK_WINDOW(g_global.r.gtk_mgr.ui.main_view.win));
	gtk_window_set_destroy_with_parent(GTK_WINDOW(
	g_global.r.gtk_mgr.ui.scene_view.win), TRUE);
	gtk_window_set_deletable(GTK_WINDOW(g_global.r.gtk_mgr.ui.scene_view.win),
	FALSE);
	g_global.r.gtk_mgr.ui.scene_view.store = gtk_tree_store_new(
	N_COLUMNS, G_TYPE_STRING, G_TYPE_DOUBLE, G_TYPE_DOUBLE, G_TYPE_DOUBLE,
	G_TYPE_BOOLEAN, G_TYPE_BOOLEAN, G_TYPE_POINTER, -1);
	populate_tree_model(g_global.r.gtk_mgr.ui.scene_view.store);
	g_global.r.gtk_mgr.ui.scene_view.tree = gtk_tree_view_new_with_model(
		GTK_TREE_MODEL(g_global.r.gtk_mgr.ui.scene_view.store));
	g_object_unref(G_OBJECT(g_global.r.gtk_mgr.ui.scene_view.store));
	render = gtk_cell_renderer_text_new();
	init_scene_view2(render);
}
