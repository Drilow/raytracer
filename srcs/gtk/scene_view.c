/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_view.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dagnear <Dagnear@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 12:54:02 by adleau            #+#    #+#             */
/*   Updated: 2018/11/16 19:54:32 by Dagnear          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <parser/parser.h>
#include <objects/object.h>
#include <fcntl.h>
#include <libft.h>
#define PIXMAP g_global.r->gtk_mgr.pixmap
#define GTKMGR g_global.r->gtk_mgr
#define SCENE_VIEW g_global.r->gtk_mgr.ui.scene_view

extern t_global		g_global;

void 				append_column_with_text(GtkWidget *tree, char *text,
									GtkCellRenderer *renderer, int en_column)
{
	GtkTreeViewColumn *column;

	column = gtk_tree_view_column_new_with_attributes(text, renderer,
                                                      "text", en_column,
                                                      NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(tree), column);
}


bool				go_throu_lights(t_light *curr)
{
	t_light	*tmp;

	tmp = g_global.r->lights;
	while (tmp)
	{
		if (curr == tmp)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

static void 		checked_row(__attribute__((unused))GtkCellRendererToggle *cell,
									gchar *path_str,
									__attribute__((unused))gpointer data)
{
	GtkTreeIter  iter;
	GtkTreePath *path;
	gboolean enabled;
	GtkTreeModel *model;
	gpointer		*obj;

	obj = NULL;
	model = NULL;
	path = gtk_tree_path_new_from_string (path_str);
	if ((model = gtk_tree_view_get_model (GTK_TREE_VIEW (SCENE_VIEW.tree))) == NULL)
        return ;
	if (gtk_tree_model_get_iter (model, &iter, path) == FALSE);
		return ;
	gtk_tree_model_get (model, &iter, CHECKED_COLUMN, &enabled, -1);
	enabled = !enabled;
	gtk_tree_store_set(SCENE_VIEW.store, &iter, CHECKED_COLUMN, enabled, -1);
	if (gtk_tree_model_get_iter(model, &iter, path) == FALSE)
		return ;
	gtk_tree_model_get (model, &iter, OBJ_REF, &obj, -1);
	if (is_obj(((t_obj*)obj)->type))
		((t_obj*)obj)->enabled = enabled;
	else if (go_throu_lights(((t_light*)obj)))
			((t_light*)obj)->enabled = enabled; // a debug
	redraw(true);
	gtk_tree_path_free (path);
}

void        select_handler(GtkTreeView *tree_view, GtkTreePath *path,
						   __attribute__((unused))GtkTreeViewColumn *column,
						   __attribute__((unused))gpointer user_data)
{
	gpointer *obj;
	GtkTreeModel *model;
	GtkTreeIter iter;

	model = NULL;
	if ((model = gtk_tree_view_get_model (tree_view)) == NULL)
		return ;
	if (gtk_tree_model_get_iter(model, &iter, path))
    {
		gtk_tree_model_get (model, &iter, OBJ_REF, &obj, -1);
		if (is_obj(((t_obj*)obj)->type))
		{
            outline_obj(((t_obj*)obj));
            edit_win(((t_obj*)obj));
		}
    }
}

void				scene_win(void)
{
	GtkTreeViewColumn *column;
	GtkCellRenderer *renderer;

	init_scene_view();
   	renderer = gtk_cell_renderer_toggle_new ();
   	gtk_cell_renderer_toggle_set_activatable(GTK_CELL_RENDERER_TOGGLE(renderer), TRUE);
   	g_signal_connect (G_OBJECT(renderer), "toggled", G_CALLBACK(checked_row), NULL);
   	column = gtk_tree_view_column_new_with_attributes ("Visible",
                                                      renderer,
                                                      "active", CHECKED_COLUMN,
                                                      NULL);
   	gtk_tree_view_column_add_attribute (column, renderer, "activatable", CHECKED_ACTIVE);
	gtk_tree_view_append_column(GTK_TREE_VIEW(SCENE_VIEW.tree), column);

  	g_signal_connect(G_OBJECT(SCENE_VIEW.tree), "row-activated",
    G_CALLBACK(select_handler), NULL);
	gtk_container_add(GTK_CONTAINER(SCENE_VIEW.win), SCENE_VIEW.tree);
    gtk_widget_show_all(SCENE_VIEW.win);
	return;
}
