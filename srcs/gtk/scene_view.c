/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_view.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dagnear <Dagnear@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 12:54:02 by adleau            #+#    #+#             */
/*   Updated: 2019/01/22 10:49:45 by adleau           ###   ########.fr       */
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

bool					go_throu_lights(t_light *curr)
{
	t_light				*tmp;

	tmp = g_global.r.lights;
	while (tmp)
	{
		if (curr == tmp)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

static void				checked_row(GtkCellRendererToggle *cell, gchar *p_str)
{
	GtkTreeIter			iter;
	GtkTreePath			*path;
	gboolean			enabled;
	GtkTreeModel		*model;
	gpointer			*obj;

	obj = NULL;
	model = gtk_tree_view_get_model(GTK_TREE_VIEW(SCENE_VIEW.tree));
	path = gtk_tree_path_new_from_string(p_str);
	if (model == NULL || !cell)
		return ;
	if (gtk_tree_model_get_iter(model, &iter, path) == FALSE)
		return ;
	gtk_tree_model_get(model, &iter, CHECKED_COLUMN, &enabled, -1);
	enabled = !enabled;
	gtk_tree_store_set(SCENE_VIEW.store, &iter, CHECKED_COLUMN, enabled, -1);
	if (gtk_tree_model_get_iter(model, &iter, path) == FALSE)
		return ;
	gtk_tree_model_get(model, &iter, OBJ_REF, &obj, -1);
	if (go_throu_lights(((t_light*)obj)))
		((t_light*)obj)->enabled = enabled;
	else if (is_obj(((t_obj*)obj)->type))
		((t_obj*)obj)->enabled = enabled;
	redraw(true);
	gtk_tree_path_free(path);
}

void					select_handler(GtkTreeView *tree, GtkTreePath *path)
{
	gpointer			*obj;
	GtkTreeModel		*model;
	GtkTreeIter			iter;

	model = NULL;
	if ((model = gtk_tree_view_get_model(tree)) == NULL)
		return ;
	if (gtk_tree_model_get_iter(model, &iter, path))
	{
		gtk_tree_model_get(model, &iter, OBJ_REF, &obj, -1);
		if (go_throu_lights(((t_light*)obj)))
			edit_light((t_light*)obj, SCENE_VIEW.win);
		else if (is_obj(((t_obj*)obj)->type))
		{
			outline_obj(((t_obj*)obj));
			edit_win(((t_obj*)obj), SCENE_VIEW.win);
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
	gtk_tree_view_column_add_attribute(column, render, "activatable",
	CHECKED_ACTIVE);
	gtk_tree_view_append_column(GTK_TREE_VIEW(SCENE_VIEW.tree), column);
	g_signal_connect(G_OBJECT(SCENE_VIEW.tree), "row-activated",
	G_CALLBACK(select_handler), NULL);
	gtk_container_add(GTK_CONTAINER(SCENE_VIEW.win), SCENE_VIEW.tree);
	SCENE_VIEW.fixed = gtk_fixed_new();
	gtk_widget_show_all(SCENE_VIEW.win);
	return ;
}
