/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_view.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpays <cpays@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 12:54:02 by adleau            #+#    #+#             */
/*   Updated: 2019/02/06 14:44:27 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>

extern t_global		g_global;

void					append_column_with_text(GtkWidget *tree, char *text,
GtkCellRenderer *renderer, int en_column)
{
	GtkTreeViewColumn	*column;

	column = NULL;
	column = gtk_tree_view_column_new_with_attributes(text, renderer,
	"text", en_column, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(tree), column);
}

static void				checked_row2(gpointer *obj, gboolean enabled,
GtkTreePath *path)
{
	if (go_throu_lights(((t_light*)obj)))
		((t_light*)obj)->enabled = enabled;
	else if (is_obj(((t_obj*)obj)->type))
		((t_obj*)obj)->enabled = enabled;
	redraw(true);
	gtk_widget_destroy(g_global.r.gtk_mgr.ui.scene_view.win);
	scene_win();
	gtk_tree_path_free(path);
}

static void				checked_row(GtkCellRendererToggle *cell, gchar *p_str)
{
	GtkTreeIter			iter;
	GtkTreePath			*path;
	gboolean			enabled;
	GtkTreeModel		*model;
	gpointer			*obj;

	if (g_global.r.gtk_mgr.ui.progress_data.window)
		return ;
	obj = NULL;
	model = NULL;
	model = gtk_tree_view_get_model(
	GTK_TREE_VIEW(g_global.r.gtk_mgr.ui.scene_view.tree));
	path = gtk_tree_path_new_from_string(p_str);
	if (model == NULL || !cell)
		return ;
	if (gtk_tree_model_get_iter(model, &iter, path) == FALSE)
		return ;
	gtk_tree_model_get(model, &iter, CHECKED_COLUMN, &enabled, -1);
	enabled = !enabled;
	gtk_tree_store_set(
	g_global.r.gtk_mgr.ui.scene_view.store, &iter, CHECKED_COLUMN, enabled, -1);
	if (gtk_tree_model_get_iter(model, &iter, path) == FALSE)
		return ;
	gtk_tree_model_get(model, &iter, OBJ_REF, &obj, -1);
	checked_row2(obj, enabled, path);
}

void					select_handler(GtkTreeView *tree, GtkTreePath *path)
{
	gpointer			*obj;
	GtkTreeModel		*model;
	GtkTreeIter			iter;

	if (g_global.r.gtk_mgr.ui.progress_data.window)
		return ;
	model = NULL;
	if ((model = gtk_tree_view_get_model(tree)) == NULL)
		return ;
	if (gtk_tree_model_get_iter(model, &iter, path))
	{
		gtk_tree_model_get(model, &iter, OBJ_REF, &obj, -1);
		if (go_throu_lights(((t_light*)obj)))
			edit_light((t_light*)obj, g_global.r.gtk_mgr.ui.scene_view.win);
		else if (is_obj(((t_obj*)obj)->type))
		{
			outline_obj(((t_obj*)obj));
			edit_win(((t_obj*)obj), g_global.r.gtk_mgr.ui.main_view.win);
		}
	}
}

void					scene_win(void)
{
	GtkTreeViewColumn	*column;
	GtkCellRenderer		*render;

	init_scene_view();
	render = gtk_cell_renderer_toggle_new();
	gtk_cell_renderer_toggle_set_activatable(GTK_CELL_RENDERER_TOGGLE(render),
		TRUE);
	g_signal_connect(G_OBJECT(render), "toggled", G_CALLBACK(checked_row),
		NULL);
	column = gtk_tree_view_column_new_with_attributes("Visible",
	render, "active", CHECKED_COLUMN, NULL);
	gtk_tree_view_set_activate_on_single_click(
	GTK_TREE_VIEW(g_global.r.gtk_mgr.ui.scene_view.tree), FALSE);
	gtk_tree_view_column_add_attribute(column, render, "activatable",
	CHECKED_ACTIVE);
	gtk_tree_view_append_column(
	GTK_TREE_VIEW(g_global.r.gtk_mgr.ui.scene_view.tree), column);
	g_signal_connect(G_OBJECT(g_global.r.gtk_mgr.ui.scene_view.tree),
	"row-activated", G_CALLBACK(select_handler), NULL);
	gtk_container_add(GTK_CONTAINER(
	g_global.r.gtk_mgr.ui.scene_view.win),
	g_global.r.gtk_mgr.ui.scene_view.tree);
	g_global.r.gtk_mgr.ui.scene_view.fixed = gtk_fixed_new();
	gtk_widget_show_all(g_global.r.gtk_mgr.ui.scene_view.win);
	return ;
}
